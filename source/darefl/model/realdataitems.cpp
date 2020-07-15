// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/datasetconvenience.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/realdataitems.h>

#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <vector>

using namespace ModelView;

// ----------------------------------------------------------------
DataGroupItem::DataGroupItem() : GraphViewportItem(::Constants::DataGroupItemType) {}

// ----------------------------------------------------------------
DataCollectionItem::DataCollectionItem() : CompoundItem(::Constants::DataCollectionItemType)
{
    registerTag(TagInfo::universalTag(T_DATA_GRROUP));
}

RealDataContainerItem::RealDataContainerItem()
    : ContainerItem(::Constants::RealDataContainerItemType)
{
}
