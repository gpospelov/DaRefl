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
    void insertData(RealDataStruct& data_struct);
    DataGroupItem* getDataGroup(const std::string tag) const;
};

// ----------------------------------------------------------------
//! This will hold all the data1Ditems unordered
class RealDataContainer : public ModelView::ContainerItem
{
public:
    RealDataContainer();
};

#endif // DAREFL_MODEL_REALDATAITEMS_H
