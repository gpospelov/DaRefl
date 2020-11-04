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
    : EditorWidget(parent), m_actions(new LayerEditorActions(this)),
      m_editorWidget(new LayerEditorWidget(this))
{
    setWindowTitle("Layer editor");
    p_toolbar = dynamic_cast<EditorToolBar*>(new LayerEditorToolBar(m_actions));
    p_toolbar->setToggleWidget(m_editorWidget);
    auto layout = new QVBoxLayout;
    layout->addWidget(p_toolbar);
    layout->addWidget(m_editorWidget);
    setLayout(layout);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

//! Set the mododel for the different items
void LayerEditor::setModels(ApplicationModels* models)
{
    m_actions->setModel(models->sampleModel());
    m_editorWidget->setModels(models);

    connect(m_editorWidget->selectionModel(), &LayerSelectionModel::selectionChanged, this,
            &LayerEditor::selectionChanged);

    m_actions->setSelectionModel(m_editorWidget->selectionModel());
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
        m_editorWidget->selectionModel()->firstSelected(),
        m_editorWidget->selectionModel()->lastSelected());
}

LayerEditor::~LayerEditor() = default;
