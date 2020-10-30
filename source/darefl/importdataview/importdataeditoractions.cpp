// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUndoStack>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>

using namespace ModelView;

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent)
    : QObject(parent), m_dataModel(model)
{
}

void ImportDataEditorActions::setSelectionModel(DataSelectionModel* selection_model)
{
    if (m_selectionModel)
        disconnect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                   &ImportDataEditorActions::onSelectionChanged);

    m_selectionModel = selection_model;

    if (m_selectionModel)
        connect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                &ImportDataEditorActions::onSelectionChanged);
}

//! Create new canvas and append it to the end of canvas container.

void ImportDataEditorActions::onAddCanvas()
{
    m_dataModel->addCanvas();
}

//! Merge selected canvases. All graphs will appear below canvas selected first.

void ImportDataEditorActions::onMergeCanvases()
{
    m_dataModel->mergeCanvases(m_selectionModel->selectedCanvas());
}

//! Delete currently selected items.

void ImportDataEditorActions::onDeleteItem()
{
    for (auto canvas : m_selectionModel->selectedCanvas())
        m_dataModel->removeCanvas(*canvas);

    for (auto graph : m_selectionModel->selectedGraphs())
        m_dataModel->removeGraph(*graph);
}

void ImportDataEditorActions::onUndo()
{
    if (!m_dataModel->undoStack())
        return;

    m_dataModel->undoStack()->undo();
}

void ImportDataEditorActions::onRedo()
{
    if (!m_dataModel->undoStack())
        return;

    m_dataModel->undoStack()->redo();
}

//! Processes changed selection. Particularly

void ImportDataEditorActions::onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{}
