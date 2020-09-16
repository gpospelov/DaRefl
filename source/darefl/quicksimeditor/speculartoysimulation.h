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
#include <vector>
#include <tuple>

class SpecularScalarTanhStrategy;

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    using sld_profile_t = std::tuple<double, double, std::vector<double>>;

    ~SpecularToySimulation();

    //! Represents results of the simulation.
    struct Result {
        std::vector<double> qvalues;
        std::vector<double> amplitudes;
    };

    //! Represents data to run specular simulations.
    struct InputData {
        std::vector<double> qvalues;
        multislice_t slice_data;
        double intensity;
    };

    SpecularToySimulation(const InputData& input_data);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    Result simulationResult() const;

    static sld_profile_t sld_profile(const multislice_t& multislice, int n_points);

private:
    size_t scanPointsCount() const;

    ModelView::ProgressHandler m_progressHandler;
    InputData m_inputData;
    Result m_specularResult;

    std::unique_ptr<SpecularScalarTanhStrategy> m_strategy;
};

#endif // DAREFL_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
