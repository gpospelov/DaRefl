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

//! Holds a collection of CanvasItem.
//! Used in the context of importing of 1D data, when user groups different GraphItem's
//! on different canvas for later plotting.

class CanvasContainerItem : public ModelView::ContainerItem
{
public:
    CanvasContainerItem();
};

//! Holds a collection of Data1DItem's with raw data as imported by the user.
//! The order of items in the collection chronologically corresponds to user activity.
//! All other plotting entities (GraphItems) are linked to data items in this container.

class RealDataContainerItem : public ModelView::ContainerItem
{
public:
    RealDataContainerItem();
};

#endif // DAREFL_MODEL_REALDATAITEMS_H
