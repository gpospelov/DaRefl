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

using namespace ModelView;

CanvasItem::CanvasItem() : GraphViewportItem(::Constants::CanvasItemType) {}

CanvasContainerItem::CanvasContainerItem() : ContainerItem(::Constants::CanvasContainerItemType) {}

ExperimentalDataContainerItem::ExperimentalDataContainerItem()
    : ContainerItem(::Constants::ExperimentalDataContainerItemType)
{
}
