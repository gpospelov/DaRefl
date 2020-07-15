// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_REALDATAITEMS_H
#define DAREFL_MODEL_REALDATAITEMS_H

#include <mvvm/model/compounditem.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <string>

namespace ModelView
{
class Data1DItem;
}

class RealDataStruct;

// ----------------------------------------------------------------
//! This will hold the data for one particular type (and pair of intensity and axis units)
class DataGroupItem : public ModelView::GraphViewportItem
{
public:
    DataGroupItem();
};

// ----------------------------------------------------------------
//! This will hold all data grouped by types
class DataCollectionItem : public ModelView::CompoundItem
{
public:
    inline static const std::string T_DATA_GRROUP = "T_DATA_GRROUP";

    DataCollectionItem();
};

//! Holds collection of Data1DItem's with raw data as imported by the user.
//! The order of items in the collection chronologically corresponds to user activity.
//! GraphItems will be linked to container's items.

class RealDataContainerItem : public ModelView::ContainerItem
{
public:
    RealDataContainerItem();
};

#endif // DAREFL_MODEL_REALDATAITEMS_H
