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

SpecularInstrumentItem::SpecularInstrumentItem()
    : ModelView::CompoundItem(::Constants::SpecularInstrumentItemType)
{
    addProperty<SpecularBeamItem>(P_BEAM);
}

SpecularBeamItem::SpecularBeamItem() : ModelView::CompoundItem(::Constants::SpecularBeamItemType)
{
    addProperty<SpecularScanGroupItem>(P_SCAN_GROUP);
}

SpecularScanGroupItem::SpecularScanGroupItem()
    : ModelView::GroupItem(::Constants::SpecularScanGroupItemType)
{
    registerItem<QSpecScanItem>("Q-scan", /*make_selected*/ true);
    init_group();
}

QSpecScanItem::QSpecScanItem() : ModelView::FixedBinAxisItem(::Constants::QSpecScanItemType) {}
