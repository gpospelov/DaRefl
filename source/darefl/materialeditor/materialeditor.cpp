// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/materialeditor/materialeditor.h>
#include <darefl/materialeditor/materialeditoractions.h>
#include <darefl/materialeditor/materialeditortoolbar.h>
#include <darefl/materialeditor/materialeditorwidget.h>
#include <darefl/model/materialmodel.h>

MaterialEditor::MaterialEditor(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), material_model(material_model),
      actions(new MaterialEditorActions(material_model, this)),
      toolbar(new MaterialEditorToolBar(actions)),
      editor_widget(new MaterialEditorWidget(material_model))
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(editor_widget);
    setLayout(layout);

    actions->setMaterialSelectionModel(editor_widget->selectionModel());
}

QSize MaterialEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize MaterialEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

MaterialEditor::~MaterialEditor() = default;
