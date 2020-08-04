// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/instrumentitems.h>
#include <darefl/model/item_constants.h>

QSpecScanItem::QSpecScanItem() : ModelView::FixedBinAxisItem(::Constants::QSpecScanItemType)
{
    setProperty(ModelView::FixedBinAxisItem::P_NBINS, 500);
    setProperty(ModelView::FixedBinAxisItem::P_MIN, 0.0);
    setProperty(ModelView::FixedBinAxisItem::P_MAX, 1.0);
}

// ----------------------------------------------------------------------------

SpecularScanGroupItem::SpecularScanGroupItem()
    : ModelView::GroupItem(::Constants::SpecularScanGroupItemType)
{
    registerItem<QSpecScanItem>("Q-scan", /*make_selected*/ true);
    init_group();
}

// ----------------------------------------------------------------------------

SpecularBeamItem::SpecularBeamItem() : ModelView::CompoundItem(::Constants::SpecularBeamItemType)
{
    addProperty(P_INTENSITY, 1.0)->setDisplayName("Intensity");
    addProperty<SpecularScanGroupItem>(P_SCAN_GROUP)->setDisplayName("Specular scan type");
}

std::vector<double> SpecularBeamItem::qScanValues() const
{
    std::vector<double> result;
    auto scan_group = item<SpecularScanGroupItem>(P_SCAN_GROUP);
    if (scan_group->currentType() == ::Constants::QSpecScanItemType)
        result = static_cast<const QSpecScanItem*>(scan_group->currentItem())->binCenters();
    return result;
}

// ----------------------------------------------------------------------------

SpecularInstrumentItem::SpecularInstrumentItem()
    : ModelView::CompoundItem(::Constants::SpecularInstrumentItemType)
{
    addProperty<SpecularBeamItem>(P_BEAM);
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const
{
    return item<SpecularBeamItem>(P_BEAM);
}
