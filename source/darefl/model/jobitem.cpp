// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/jobitem.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

JobItem::JobItem() : ModelView::CompoundItem(::Constants::JobItemType)
{
    setup_sld_viewport();
    setup_specular_viewport();
}

Data1DItem* JobItem::sld_data() const
{
    return item<Data1DItem>(P_SLD_DATA);
}

GraphViewportItem* JobItem::sld_viewport() const
{
    return item<GraphViewportItem>(P_SLD_VIEWPORT);
}

Data1DItem* JobItem::specular_data() const
{
    return item<Data1DItem>(P_SPECULAR_DATA);
}

CanvasItem* JobItem::specular_viewport() const
{
    return item<CanvasItem>(P_SPECULAR_VIEWPORT);
}

void JobItem::setup_sld_viewport()
{
    auto data = addProperty<Data1DItem>(P_SLD_DATA);
    auto viewport = addProperty<GraphViewportItem>(P_SLD_VIEWPORT);
    auto graph = std::make_unique<GraphItem>();
    graph->setDataItem(data);
    viewport->insertItem(graph.release(), {ViewportItem::T_ITEMS, 0});
}

void JobItem::setup_specular_viewport()
{
    auto data = addProperty<Data1DItem>(P_SPECULAR_DATA);
    auto viewport = addProperty<CanvasItem>(P_SPECULAR_VIEWPORT);
    auto graph = std::make_unique<GraphItem>();
    graph->setDataItem(data);
    viewport->insertItem(graph.release(), {ViewportItem::T_ITEMS, 0});
}
