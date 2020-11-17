// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
#define DAREFL_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H

#include <darefl/quicksimeditor/quicksim_types.h>
#include <memory>
#include <mvvm/utils/progresshandler.h>
#include <tuple>
#include <vector>

class SpecularScalarTanhStrategy;

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    using sld_profile_t = std::tuple<double, double, std::vector<double>>;

    ~SpecularToySimulation();

    SpecularToySimulation(const SimulationInput& input_data);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    SimulationResult simulationResult() const;

    static sld_profile_t sld_profile(const multislice_t& multislice, int n_points);

private:
    size_t scanPointsCount() const;

    ModelView::ProgressHandler m_progressHandler;
    SimulationInput m_inputData;
    SimulationResult m_specularResult;

    std::unique_ptr<SpecularScalarTanhStrategy> m_strategy;
};

#endif // DAREFL_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
