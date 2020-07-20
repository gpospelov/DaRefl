// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/item_constants.h>

#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <mvvm/model/mvvm_types.h>
#include <set>

//! The constructor
DataSelectionModel::DataSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent)
{
    // FIXME cover with unit tests after implementing ViewItemSelectionModel
    connect(view_model, &ModelView::ViewModel::modelAboutToBeReset, [this]() { clearSelection(); });
}

//! Set the selection on a single item
void DataSelectionModel::selectItem(ModelView::SessionItem* item)
{
    selectItems({item});
}

//! Set the selection on a list of items
void DataSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items)
{
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item);

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
}

//! Return the selected items
std::vector<ModelView::SessionItem*> DataSelectionModel::selectedItems() const
{
    std::vector<ModelView::SessionItem*> result;

    // removing nullptr and duplicates, preserving the order
    // FIXME move to utility function on board of qt-mvvm

    auto items = ModelView::Utils::ItemsFromIndex(selectedIndexes());
    std::set<ModelView::SessionItem*> unique(items.begin(), items.end());

    std::copy_if(items.begin(), items.end(), std::back_inserter(result),
                 [&unique](auto x) { return x && unique.find(x) != unique.end(); });

    return result;
}

const ModelView::ViewModel* DataSelectionModel::viewModel() const
{
    return static_cast<const ModelView::ViewModel*>(model());
}

//! Returns currently selected canvas, or returns 'nullptr'.
//! If more than one canvas is selected, will return the first one.
//! If the underlying graph is selected, will return canvas to which this graph belongs to.

CanvasItem* DataSelectionModel::selectedCanvas() const
{
    for (auto item : selectedItems()) {
        if (item->modelType() == ::Constants::CanvasItemType)
            return static_cast<CanvasItem*>(item);
        else if(item->modelType() == ModelView::Constants::GraphItemType)
            return static_cast<CanvasItem*>(item->parent());
    }
    return nullptr;
}
