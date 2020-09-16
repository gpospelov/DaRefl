// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_JOBMANAGER_H
#define DAREFL_QUICKSIMEDITOR_JOBMANAGER_H

#include <QObject>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <mvvm/utils/threadsafestack.h>

//! Handles all thread activity for running job simulation in the background.

class JobManager : public QObject
{
    Q_OBJECT
public:
    JobManager(QObject* parent = nullptr);
    ~JobManager() override;

    SpecularToySimulation::Result simulationResult();

signals:
    void progressChanged(int value);
    void simulationCompleted();

public slots:
    void requestSimulation(const multislice_t& multislice, const std::vector<double>& qvalues,
                           double intensity);
    void onInterruptRequest();

private:
    void wait_and_run();

    std::thread m_sim_thread;
    ModelView::threadsafe_stack<SpecularToySimulation::InputData> m_requested_values;
    ModelView::threadsafe_stack<SpecularToySimulation::Result> m_simulation_results;
    std::atomic<bool> m_is_running;
    bool m_interrupt_request{false};
};

#endif // DAREFL_QUICKSIMEDITOR_JOBMANAGER_H
