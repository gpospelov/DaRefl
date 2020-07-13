// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/materialeditor/materialeditorwidget.h>
#include <darefl/materialeditor/materialselectionmodel.h>
#include <darefl/materialeditor/materialtableview.h>
#include <darefl/materialeditor/materialtreeview.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/materialitems.h>
#include <darefl/model/materialmodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

MaterialEditorWidget::MaterialEditorWidget(QWidget* parent)
    : QWidget(parent), material_view(new MaterialTreeView),
      m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(material_view);
    setLayout(layout);
    material_view->setItemDelegate(m_delegate.get());
}

MaterialEditorWidget::~MaterialEditorWidget() = default;

void MaterialEditorWidget::setModels(ApplicationModels* models)
{
    material_model = models->materialModel();
    view_model = ModelView::Utils::CreatePropertyTableViewModel(material_model);
    selection_model = new MaterialSelectionModel(view_model.get(), this);
    view_model->setRootSessionItem(
        ModelView::Utils::TopItem<MaterialContainerItem>(material_model));
    material_view->setModel(view_model.get());
    material_view->setSelectionModel(selection_model);
}

MaterialSelectionModel* MaterialEditorWidget::selectionModel() const
{
    return selection_model;
}
