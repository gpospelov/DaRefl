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
#include <darefl/model/materialitems.h>
#include <darefl/model/materialmodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

MaterialEditorWidget::MaterialEditorWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      view_model(ModelView::Utils::CreatePropertyTableViewModel(material_model)),
      selection_model(new MaterialSelectionModel(view_model.get(), this)),
      material_view(new MaterialTreeView),
      m_delegate(std::make_unique<ModelView::ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(material_view);
    setLayout(layout);

    view_model->setRootSessionItem(
        ModelView::Utils::TopItem<MaterialContainerItem>(material_model));
    material_view->setModel(view_model.get());
    material_view->setSelectionModel(selection_model);
    material_view->setItemDelegate(m_delegate.get());
}

MaterialEditorWidget::~MaterialEditorWidget() = default;

MaterialSelectionModel* MaterialEditorWidget::selectionModel() const
{
    return selection_model;
}
