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
#include <darefl/model/realdata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/modelutils.h>

using namespace ModelView;

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model,
                                                 DataSelectionModel* selectionModel,
                                                 QObject* parent)
    : QObject(parent), m_dataModel(model), m_selectionModel(selectionModel)
{
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
    std::vector<SessionItem*> items_to_delete = m_selectionModel->selectedItems();
    m_dataModel->removeDataFromCollection(items_to_delete);
}

void ImportDataEditorActions::onResetAll()
{
    auto data_node = ModelView::Utils::TopItem<CanvasContainerItem>(m_dataModel);
    m_dataModel->removeAllDataFromCollection(data_node);
}
