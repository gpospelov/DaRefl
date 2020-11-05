// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H

#include <QObject>
#include <darefl/quicksimeditor/quicksim_types.h>
#include <memory>

namespace ModelView
{
class ModelHasChangedController;
}

class ApplicationModels;
class JobManager;
class JobModel;
class InstrumentModel;

//! Provides quick reflectometry simulations on any change of SampleModel and MaterialModel.
//! Listens for any change in SampleModel and MaterialModel, extracts the data needed for
//! the simulation, and then submit simulation request to JobManager. As soon as JobManager reports
//! about completed simulations, extract results from there and put them into JobModel.

class QuickSimController : public QObject
{
    Q_OBJECT

public:
    QuickSimController(QObject* parent = nullptr);
    ~QuickSimController();

    void setModels(ApplicationModels* models);

signals:
    void progressChanged(int value);

public slots:
    void onInterruptRequest();
    void onRealTimeRequest(bool status);
    void onRunSimulationRequest();

private slots:
    void onMultiLayerChange();
    void onSimulationCompleted();

private:
    void process_multilayer(bool submit_simulation = false);
    void update_sld_profile(const multislice_t& multilayer);
    void submit_specular_simulation(const multislice_t& multislice);
    void setup_jobmanager_connections();

    JobModel* jobModel() const;
    InstrumentModel* instrumentModel() const;

    ApplicationModels* m_models{nullptr};
    JobManager* job_manager{nullptr};

    bool in_realtime_mode; //! Run simulation on every parameter change.

    std::unique_ptr<ModelView::ModelHasChangedController> m_materialChangedController;
    std::unique_ptr<ModelView::ModelHasChangedController> m_sampleChangedController;
    std::unique_ptr<ModelView::ModelHasChangedController> m_instrumentChangedController;
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMCONTROLLER_H
