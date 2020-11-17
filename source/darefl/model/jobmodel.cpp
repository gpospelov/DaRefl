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
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <darefl/quicksimeditor/quicksim_types.h>

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

Data1DItem* JobModel::sld_data() const
{
    return job_item()->sld_data();
}

GraphViewportItem* JobModel::sld_viewport() const
{
    return job_item()->sld_viewport();
}

Data1DItem* JobModel::specular_data() const
{
    return job_item()->specular_data();
}

CanvasItem* JobModel::specular_viewport() const
{
    return job_item()->specular_viewport();
}

void JobModel::updateReferenceGraphFrom(const SpecularInstrumentItem* instrument)
{
    job_item()->updateReferenceGraphFrom(instrument);
}

//! Set simulation results to JobItem.

void JobModel::setJobResult(const SimulationResult& data)
{
    auto [qvalues, amplitudes] = data;
    specular_data()->setAxis(ModelView::PointwiseAxisItem::create(qvalues));
    specular_data()->setValues(amplitudes);
}

JobItem* JobModel::job_item() const
{
    return Utils::TopItem<JobItem>(this);
}
