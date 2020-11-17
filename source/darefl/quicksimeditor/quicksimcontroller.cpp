// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/applicationmodels.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <darefl/model/sampleitems.h>
#include <darefl/model/materialmodel.h>
#include <darefl/model/samplemodel.h>
#include <darefl/quicksimeditor/jobmanager.h>
#include <darefl/quicksimeditor/quicksimcontroller.h>
#include <darefl/quicksimeditor/quicksimutils.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <darefl/core/app_constants.h>
#include <mvvm/project/modelhaschangedcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

namespace
{
const int profile_points_count = 1000;
}

QuickSimController::QuickSimController(QObject* parent)
    : QObject(parent), job_manager(new JobManager(this)),
      in_realtime_mode(Constants::live_simulation_default_on)
{
}

QuickSimController::~QuickSimController() = default;

void QuickSimController::setModels(ApplicationModels* models)
{
    m_models = models;

    auto on_model_change = [this]() { onMultiLayerChange(); };
    m_materialChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->materialModel(), on_model_change);
    m_sampleChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->sampleModel(), on_model_change);
    m_instrumentChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->instrumentModel(), on_model_change);

    setup_jobmanager_connections();

    onMultiLayerChange();
    jobModel()->sld_viewport()->update_viewport();
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
    auto [qvalues, amplitudes] = job_manager->simulationResult();
    auto data = jobModel()->specular_data();
    data->setAxis(ModelView::PointwiseAxisItem::create(qvalues));
    data->setValues(amplitudes);
}

//! Constructs multislice, calculates profile and submits specular simulation.

void QuickSimController::process_multilayer(bool submit_simulation)
{
    auto multilayer = m_models->sampleModel()->topItem<MultiLayerItem>();
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
    auto data = jobModel()->sld_data();
    data->setAxis(ModelView::FixedBinAxisItem::create(values.size(), xmin, xmax));
    data->setValues(values);
}

//! Submit data to JobManager for consequent specular simulation in a separate thread.

void QuickSimController::submit_specular_simulation(const multislice_t& multislice)
{
    auto instrument = instrumentModel()->topItem<SpecularInstrumentItem>();
    auto beam = instrument->beamItem();
    job_manager->requestSimulation(multislice, beam->qScanValues(), beam->intensity());
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

JobModel* QuickSimController::jobModel() const
{
    return m_models->jobModel();
}

InstrumentModel* QuickSimController::instrumentModel() const
{
    return m_models->instrumentModel();
}
