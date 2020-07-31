// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/applicationmodels.h>
#include <darefl/model/jobmodel.h>
#include <darefl/model/layeritems.h>
#include <darefl/model/materialmodel.h>
#include <darefl/model/samplemodel.h>
#include <darefl/quicksimeditor/jobmanager.h>
#include <darefl/quicksimeditor/materialprofile.h>
#include <darefl/quicksimeditor/quicksimcontroller.h>
#include <darefl/quicksimeditor/quicksimutils.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/project/modelhaschangedcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphviewportitem.h>

namespace
{
const int profile_points_count = 400;
}

QuickSimController::QuickSimController(QObject* parent)
    : QObject(parent), job_manager(new JobManager(this))
{
}

QuickSimController::~QuickSimController() = default;

void QuickSimController::setModels(ApplicationModels* models)
{
    sample_model = models->sampleModel();
    material_model = models->materialModel();
    job_model = models->jobModel();

    auto on_model_change = [this]() { onMultiLayerChange(); };
    m_materialChangedController =
        std::make_unique<ModelView::ModelHasChangedController>(material_model, on_model_change);
    m_sampleChangedController =
        std::make_unique<ModelView::ModelHasChangedController>(sample_model, on_model_change);

    setup_jobmanager_connections();

    onMultiLayerChange();
    job_model->sld_viewport()->update_viewport();
}

//! Requests interruption of running simulaitons.

void QuickSimController::onInterruptRequest()
{
    job_manager->onInterruptRequest();
}

void QuickSimController::onRealTimeRequest(bool status)
{
    in_realtime_mode = status;
}

//! Processes multilayer on request. Doesn't work in real time mode.

void QuickSimController::onRunSimulationRequest()
{
    if (in_realtime_mode)
        return;
    process_multilayer(/*submit_simulation*/ true);
}

//! Processes multilayer on any model change. Works only in realtime mode.

void QuickSimController::onMultiLayerChange()
{
    process_multilayer(/*submit_simulation*/ in_realtime_mode);
}

//! Takes simulation results from JobManager and write into the model.

void QuickSimController::onSimulationCompleted()
{
    if (!job_model)
        return;

    auto [xmin, xmax, values] = job_manager->simulationResult();
    auto data = job_model->specular_data();
    data->setAxis(ModelView::FixedBinAxisItem::create(values.size(), xmin, xmax));
    data->setContent(values);
}

//! Constructs multislice, calculates profile and submits specular simulation.

void QuickSimController::process_multilayer(bool submit_simulation)
{
    auto multilayer = ModelView::Utils::TopItem<MultiLayerItem>(sample_model);
    auto slices = ::Utils::CreateMultiSlice(*multilayer);
    update_sld_profile(slices);
    if (submit_simulation)
        submit_specular_simulation(slices);
}

//! Calculates sld profile from slice and immediately update data items.

void QuickSimController::update_sld_profile(const multislice_t& multislice)
{
    auto [xmin, xmax, values] =
        SpecularToySimulation::sld_profile(multislice, profile_points_count);
    auto data = job_model->sld_data();
    data->setAxis(ModelView::FixedBinAxisItem::create(values.size(), xmin, xmax));
    data->setContent(values);
}

//! Submit data to JobManager for consequent specular simulation in a separate thread.

void QuickSimController::submit_specular_simulation(const multislice_t& multislice)
{
    job_manager->requestSimulation(multislice);
}

//! Connect signals going from JobManager. Connections are made queued since signals are emitted
//! from non-GUI thread and we want to deal with widgets.

void QuickSimController::setup_jobmanager_connections()
{

    // Simulation progress is propagated from JobManager to this controller for further forwarding.
    connect(job_manager, &JobManager::progressChanged, this, &QuickSimController::progressChanged,
            Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to this controller.
    connect(job_manager, &JobManager::simulationCompleted, this,
            &QuickSimController::onSimulationCompleted, Qt::QueuedConnection);
}
