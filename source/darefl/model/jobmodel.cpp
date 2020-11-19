// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldataitems.h>
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

GraphViewportItem* JobModel::sldViewport() const
{
    return jobItem()->sldViewport();
}

CanvasItem* JobModel::specularViewport() const
{
    return jobItem()->specularViewport();
}

GraphViewportItem* JobModel::diffViewport() const
{
    return jobItem()->diffViewport();
}

void JobModel::updateReferenceGraph(const ModelView::GraphItem* graph)
{
    jobItem()->updateReferenceGraph(graph);
}

//! Updates specular data in JobItem from simulation results.

void JobModel::updateSpecularData(const SimulationResult& data)
{
    auto specularData = jobItem()->specularData();
    specularData->setAxis(ModelView::PointwiseAxisItem::create(data.qvalues));
    specularData->setValues(data.amplitudes);

    // updating difference graph
    jobItem()->updateDifferenceData();
}

//! Updates SLD profile data.

void JobModel::updateSLDProfile(const SLDProfile& data)
{
    auto sldData = jobItem()->sldData();
    sldData->setAxis(FixedBinAxisItem::create(data.sld_real_values.size(), data.zmin, data.zmax));
    sldData->setValues(data.sld_real_values);
}

JobItem* JobModel::jobItem() const
{
    return Utils::TopItem<JobItem>(this);
}
