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
#include <darefl/model/applicationmodels.h>
#include <darefl/model/materialmodel.h>

MaterialEditor::MaterialEditor(QWidget* parent)
    : QWidget(parent), p_actions(new MaterialEditorActions(this)),
      p_toolbar(new MaterialEditorToolBar(p_actions)), p_editor_widget(new MaterialEditorWidget)
{
    setWindowTitle("Material editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(p_toolbar);
    layout->addWidget(p_editor_widget);
    setLayout(layout);
}

//! Set the mododel for the different items
void MaterialEditor::setModels(ApplicationModels* models)
{
    p_editor_widget->setModels(models);
    p_actions->setModel(models->materialModel());
    p_actions->setMaterialSelectionModel(p_editor_widget->selectionModel());
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
