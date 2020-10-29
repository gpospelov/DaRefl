// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>

#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

#include <algorithm>
#include <cmath>

using namespace ModelView;

namespace
{

const std::string model_name{"ExperimentalDataModel"};

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<CanvasItem>();
    result->registerItem<CanvasContainerItem>();
    result->registerItem<ExperimentalDataContainerItem>();
    return result;
}

} // namespace

ExperimentalDataModel::ExperimentalDataModel() : SessionModel(model_name)
{
    init_model();
}

ExperimentalDataModel::ExperimentalDataModel(std::shared_ptr<ItemPool> pool)
    : SessionModel(model_name, pool)

{
    init_model();
}

//! Returns the canvas container of the model.

CanvasContainerItem* ExperimentalDataModel::canvasContainer() const
{
    return topItem<CanvasContainerItem>();
}

//! Returns the data container of the model.

ExperimentalDataContainerItem* ExperimentalDataModel::dataContainer() const
{
    return topItem<ExperimentalDataContainerItem>();
}

CanvasItem* ExperimentalDataModel::addCanvas()
{
    return insertItem<CanvasItem>(canvasContainer());
}

//! Adds graph to 'target_canvas' and returns the result.
//! Internally add Data1DItem object to ExperimentalDataContainerItem,
//! and set it to GraphItem.

ModelView::GraphItem* ExperimentalDataModel::addGraph(const RealDataStruct& data_struct,
                                                      CanvasItem& target_canvas)
{
    auto result = insertItem<GraphItem>(&target_canvas);

    auto data = insertItem<Data1DItem>(dataContainer());
    data->setAxis(PointwiseAxisItem::create(data_struct.axis));
    data->setContent(data_struct.data);
    result->setDataItem(data);

    return result;
}

//! Remove graph from the model. Underlying DataItem will be removed too.

void ExperimentalDataModel::removeGraph(GraphItem& graph)
{
    auto dataItem = graph.dataItem();
    removeItem(graph.parent(), graph.tagRow());
    removeItem(dataItem->parent(), dataItem->tagRow());
}

//! Remove canvas with all its graphs.

void ExperimentalDataModel::removeCanvas(CanvasItem& canvas)
{
    for (auto graph : canvas.graphItems())
        removeGraph(*graph);
    removeItem(canvas.parent(), canvas.tagRow());
}

//! Check if an item should be editable or not
bool ExperimentalDataModel::itemEditable(ModelView::SessionItem* item) const
{
    if (dynamic_cast<GraphItem*>(item))
        return true;
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    if (dynamic_cast<CanvasContainerItem*>(item))
        return true;
    return false;
}

//! Check if an item should be allowed to be dragged
bool ExperimentalDataModel::dragEnabled(ModelView::SessionItem* item) const
{
    if (dynamic_cast<GraphItem*>(item))
        return true;
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    return false;
}

//! Check if an item should be allowed to be receive drops
bool ExperimentalDataModel::dropEnabled(ModelView::SessionItem* item) const
{
    if (dynamic_cast<CanvasItem*>(item))
        return true;
    return false;
}

//! process to the move of an item
bool ExperimentalDataModel::dragDropItem(ModelView::SessionItem* item,
                                         ModelView::SessionItem* target, int row)
{
    if (dynamic_cast<GraphItem*>(item) && dynamic_cast<CanvasItem*>(target)
        && target != item->parent()) {
        moveItem(dynamic_cast<GraphItem*>(item), dynamic_cast<CanvasItem*>(target),
                 {dynamic_cast<CanvasItem*>(target)->defaultTag(), row});
        return true;
    }

    if (dynamic_cast<CanvasItem*>(item) && dynamic_cast<CanvasItem*>(target)
        && target != item->parent()) {
        mergeItems(std::vector<ModelView::SessionItem*>{target, item});
        return true;
    }

    return false;
}

//! Merges all items present into the first of the vector
bool ExperimentalDataModel::mergeItems(std::vector<ModelView::SessionItem*> items)
{
    if (items.size() < 1)
        return false;

    for (int i = 1; i < items.size(); ++i) {
        for (auto child : items.at(i)->children()) {
            if (child->parent()->isSinglePropertyTag(child->tag()))
                continue;
            moveItem(child, items.at(0), {child->tag(), -1});
        }
        removeItem(items.at(i)->parent(), items.at(i)->tagRow());
    }

    return true;
}

void ExperimentalDataModel::init_model()
{
    setItemCatalogue(CreateItemCatalogue());

    insertItem<ExperimentalDataContainerItem>(rootItem());
    insertItem<CanvasContainerItem>(rootItem());

    setUndoRedoEnabled(true);
}
