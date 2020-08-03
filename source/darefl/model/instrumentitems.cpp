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
}

SpecularBeamItem::SpecularBeamItem() : ModelView::CompoundItem(::Constants::SpecularBeamItemType) {}

SpecularScanGroupItem::SpecularScanGroupItem()
    : ModelView::GroupItem(::Constants::SpecularScanGroupItemType)
{
}

QSpecScanItem::QSpecScanItem() : ModelView::CompoundItem(::Constants::QSpecScanItemType) {}
