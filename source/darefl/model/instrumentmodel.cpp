// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <mvvm/model/itemcatalogue.h>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<SpecularInstrumentItem>();
    result->registerItem<SpecularBeamItem>();
    result->registerItem<SpecularScanGroupItem>();
    result->registerItem<QSpecScanItem>();
    return result;
}

} // namespace

InstrumentModel::InstrumentModel() : ModelView::SessionModel("InstrumentModel")
{
    setItemCatalogue(CreateItemCatalogue());

    insertItem<SpecularInstrumentItem>();
}
