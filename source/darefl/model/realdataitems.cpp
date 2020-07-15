// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/datasetconvenience.h>
#include <darefl/model/realdataitems.h>
#include <darefl/model/item_constants.h>

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

//! Check if a data group tag is present and return it if it is
DataGroupItem* DataCollectionItem::getDataGroup(const std::string tag) const
{
    std::vector<SessionItem*> items = getItems(T_DATA_GRROUP);
    auto found = std::find_if(items.begin(), items.end(),
                              [&tag](const SessionItem* item) { return item->isTag(tag); });

    if (found == items.end())
        return nullptr;
    else
        return dynamic_cast<DataGroupItem*>(*found);
}

// ----------------------------------------------------------------
RealDataContainer::RealDataContainer() : ContainerItem() {}
