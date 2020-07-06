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

LayerEditor::LayerEditor(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), actions(new LayerEditorActions(models->sampleModel(), this)),
      toolbar(new LayerEditorToolBar(actions)), editor_widget(new LayerEditorWidget(models))
{
    setWindowTitle("Layer editor");

    auto layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(editor_widget);
    setLayout(layout);

    connect(editor_widget->selectionModel(), &LayerSelectionModel::selectionChanged, this,
            &LayerEditor::selectionChanged);

    actions->setSelectionModel(editor_widget->selectionModel());
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
    toolbar->updateToolButtonStates(editor_widget->selectionModel()->firstSelected(),
                                    editor_widget->selectionModel()->lastSelected());
}

LayerEditor::~LayerEditor() = default;
