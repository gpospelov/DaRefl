// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/modelutils.h>
#include <QUndoStack>


using namespace ModelView;

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model,
                                                 QObject* parent)
    : QObject(parent), m_dataModel(model)
{
}

void ImportDataEditorActions::setSelectionModel(DataSelectionModel* selection_model)
{
    m_selectionModel = selection_model;
}

//! Create a new data grou item in the current data collection item

void ImportDataEditorActions::onAddDataGroup()
{
    auto data_node = ModelView::Utils::TopItem<CanvasContainerItem>(m_dataModel);
    m_dataModel->addDataToCollection(RealDataStruct(), data_node, nullptr);
}

//! Merge the selected actions

void ImportDataEditorActions::onMergeDataGroups()
{
    auto items = m_selectionModel->selectedItems();
    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    if (!m_dataModel->checkAllGroup(items))
        return;

    m_dataModel->mergeItems(items);
}

//! Delete the currently selected item

void ImportDataEditorActions::onDeleteItem()
{
    m_dataModel->removeDataFromCollection(m_selectionModel->selectedItems());
}

void ImportDataEditorActions::onClearCanvasContainer()
{
    auto data_node = ModelView::Utils::TopItem<CanvasContainerItem>(m_dataModel);
    m_dataModel->removeAllDataFromCollection(data_node);
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
