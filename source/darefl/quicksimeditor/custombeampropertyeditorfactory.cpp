// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QModelIndex>
#include <algorithm>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <darefl/model/materialmodel.h>
#include <darefl/quicksimeditor/custombeampropertyeditorfactory.h>
#include <mvvm/editors/externalpropertycomboeditor.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

namespace
{

//! Returns vector of ExternalProperty representing imported graphs.
//! Use "Undefined graph" as a first item in a list.

std::vector<ModelView::ExternalProperty> get_choice_of_graphs(ExperimentalDataModel* model)
{
    std::vector<ModelView::ExternalProperty> result{ExternalProperty("Undefined", QColor(Qt::red))};

    for (auto graph : Utils::FindItems<GraphItem>(model)) {
        std::string name = graph->parent()->displayName() + "/" + graph->displayName();
        auto color = graph->property<QColor>(GraphItem::P_COLOR);
        result.push_back(ExternalProperty(name, color, graph->identifier()));
    }
    return result;
}
} // namespace

CustomBeamPropertyEditorFactory::~CustomBeamPropertyEditorFactory() = default;

CustomBeamPropertyEditorFactory::CustomBeamPropertyEditorFactory(ApplicationModels* models)
    : m_models(models)
{
}

std::unique_ptr<CustomEditor>
CustomBeamPropertyEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value)) {
        auto choice_callback = [this]() { return get_choice_of_graphs(m_models->realDataModel()); };
        return std::make_unique<ExternalPropertyComboEditor>(choice_callback);
    } else {
        return DefaultEditorFactory::createEditor(index);
    }
}
