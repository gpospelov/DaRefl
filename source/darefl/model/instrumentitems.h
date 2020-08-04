// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_INSTRUMENTITEM_H
#define DAREFL_MODEL_INSTRUMENTITEM_H

//! @file instrumentitems.h
//! Collection of items to construct specular instrument.

#include <mvvm/model/compounditem.h>
#include <mvvm/model/groupitem.h>
#include <mvvm/standarditems/axisitems.h>

//! Represents specular instrument.

class SpecularBeamItem;

class SpecularInstrumentItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_BEAM = "P_BEAM";

    SpecularInstrumentItem();

    SpecularBeamItem* beamItem() const;
};

//! Represents specular beam, contains settings of scan parameters.

class SpecularBeamItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_INTENSITY = "P_INTENSITY";
    static inline const std::string P_SCAN_GROUP = "P_SCAN_GROUP";

    SpecularBeamItem();

    std::vector<double> qScanValues() const;
};

//! Represent selection of possible specular scans.

class SpecularScanGroupItem : public ModelView::GroupItem
{
public:
    SpecularScanGroupItem();
};

//! Represents Q-space specular scan.

class QSpecScanItem : public ModelView::FixedBinAxisItem
{
public:
    static inline const std::string P_QMIN = "P_BEAM";
    QSpecScanItem();
};

#endif // DAREFL_MODEL_INSTRUMENTITEM_H
