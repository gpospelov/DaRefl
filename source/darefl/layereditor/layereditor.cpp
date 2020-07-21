// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/layereditor/layereditor.h>
#include <darefl/layereditor/layereditoractions.h>
#include <darefl/layereditor/layereditortoolbar.h>
#include <darefl/layereditor/layereditorwidget.h>
#include <darefl/layereditor/layerselectionmodel.h>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/model/applicationmodels.h>

LayerEditor::LayerEditor(QWidget* parent)
    : EditorWidget(parent), p_actions(new LayerEditorActions(this)),
      p_editor_widget(new LayerEditorWidget(this))
{
    setWindowTitle("Layer editor");
    p_toolbar = dynamic_cast<EditorToolBar*>(new LayerEditorToolBar(p_actions));
    p_toolbar->setToggleWidget(p_editor_widget);
    auto layout = new QVBoxLayout;
    layout->addWidget(p_toolbar);
    layout->addWidget(p_editor_widget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

//! Set the mododel for the different items
void LayerEditor::setModels(ApplicationModels* models)
{
    p_actions->setModel(models->sampleModel());
    p_editor_widget->setModels(models);

    connect(p_editor_widget->selectionModel(), &LayerSelectionModel::selectionChanged, this,
            &LayerEditor::selectionChanged);

    p_actions->setSelectionModel(p_editor_widget->selectionModel());
}

QSize LayerEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize LayerEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

void LayerEditor::selectionChanged()
{
    dynamic_cast<LayerEditorToolBar*>(p_toolbar)->updateToolButtonStates(
        p_editor_widget->selectionModel()->firstSelected(),
        p_editor_widget->selectionModel()->lastSelected());
}

LayerEditor::~LayerEditor() = default;
