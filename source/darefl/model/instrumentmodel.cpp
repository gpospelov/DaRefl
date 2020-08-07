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

const std::string model_name = "InstrumentModel";

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<SpecularInstrumentItem>();
    result->registerItem<SpecularBeamItem>();
    result->registerItem<SpecularScanGroupItem>();
    result->registerItem<QSpecScanItem>();
    result->registerItem<ExperimentalScanItem>();
    return result;
}

} // namespace

InstrumentModel::InstrumentModel() : ModelView::SessionModel("InstrumentModel")
{
    init_model();
}

InstrumentModel::InstrumentModel(std::shared_ptr<ItemPool> pool)
    : ModelView::SessionModel(model_name, pool)
{
    init_model();
}

void InstrumentModel::init_model()
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<SpecularInstrumentItem>();
}
