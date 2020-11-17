// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <darefl/quicksimeditor/quicksim_types.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

namespace
{

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<JobItem>();
    result->registerItem<CanvasItem>();
    result->registerItem<SLDCanvasItem>();
    return result;
}

} // namespace

JobModel::JobModel(std::shared_ptr<ItemPool> pool) : SessionModel("JobModel", pool)
{
    setItemCatalogue(CreateItemCatalogue());
    insertItem<JobItem>();
}

Data1DItem* JobModel::sldData() const
{
    return job_item()->sld_data();
}

GraphViewportItem* JobModel::sldViewport() const
{
    return job_item()->sld_viewport();
}

Data1DItem* JobModel::specularData() const
{
    return job_item()->specular_data();
}

CanvasItem* JobModel::specularViewport() const
{
    return job_item()->specular_viewport();
}

void JobModel::updateReferenceGraphFrom(const SpecularInstrumentItem* instrument)
{
    job_item()->updateReferenceGraphFrom(instrument);
}

//! Updates specular data in JobItem from simulation results.

void JobModel::updateSpecularData(const SimulationResult& data)
{
    specularData()->setAxis(ModelView::PointwiseAxisItem::create(data.qvalues));
    specularData()->setValues(data.amplitudes);
}

//! Updates SLD profile data.

void JobModel::updateSLDProfile(const SLDProfile& data)
{
    sldData()->setAxis(FixedBinAxisItem::create(data.sld_real_values.size(), data.zmin, data.zmax));
    sldData()->setValues(data.sld_real_values);
}

JobItem* JobModel::job_item() const
{
    return Utils::TopItem<JobItem>(this);
}
