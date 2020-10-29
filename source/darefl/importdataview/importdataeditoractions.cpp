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
#include <mvvm/model/modelutils.h>

using namespace ModelView;

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent)
    : QObject(parent), m_dataModel(model)
{
}

void ImportDataEditorActions::setSelectionModel(DataSelectionModel* selection_model)
{
    m_selectionModel = selection_model;
}

//! Create new canvas and append it to the end of canvas container.

void ImportDataEditorActions::onAddCanvas()
{
    m_dataModel->addCanvas();
}

//! Merge the selected actions

void ImportDataEditorActions::onMergeCanvas()
{
    //    auto items = m_selectionModel->selectedItems();
    //    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    //    if (!m_dataModel->checkAllGroup(items))
    //        return;

    //    m_dataModel->mergeItems(items);
    // FIXME restore
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
