// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/item_constants.h>
#include <darefl/model/experimentaldataitems.h>
#include <mvvm/standarditems/axisitems.h>

using namespace ModelView;

CanvasItem::CanvasItem() : GraphViewportItem(::Constants::CanvasItemType)
{
    yAxis()->setProperty(ViewportAxisItem::P_IS_LOG, true);
}

std::pair<double, double> CanvasItem::data_yaxis_range() const
{
    auto [ymin, ymax] = GraphViewportItem::data_yaxis_range();
    return {ymin, ymax*2.0};
}

CanvasContainerItem::CanvasContainerItem() : ContainerItem(::Constants::CanvasContainerItemType) {}

ExperimentalDataContainerItem::ExperimentalDataContainerItem()
    : ContainerItem(::Constants::ExperimentalDataContainerItemType)
{
}
