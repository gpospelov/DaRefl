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

//! Represents Q-space specular scan.

class QSpecScanItem : public ModelView::FixedBinAxisItem
{
public:
    static inline const std::string P_QMIN = "P_QMIN";
    QSpecScanItem();
};

//! Represents scan according to imported experimental data.

class ExperimentalScanItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_IMPORTED_DATA = "P_IMPORTED_DATA";
    ExperimentalScanItem();
};

//! Represent selection of possible specular scans.

class SpecularScanGroupItem : public ModelView::GroupItem
{
public:
    SpecularScanGroupItem();
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

//! Represents specular instrument.

class SpecularInstrumentItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_BEAM = "P_BEAM";

    SpecularInstrumentItem();

    SpecularBeamItem* beamItem() const;
};

#endif // DAREFL_MODEL_INSTRUMENTITEM_H
