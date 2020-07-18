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

#include <darefl/quicksimeditor/materialprofile.h>
#include <minikernel/MultiLayer/SpecularScalarTanhStrategy.h>
#include <mvvm/utils/progresshandler.h>
#include <vector>
#include <memory>

//! Toy simulation to calculate "specular reflectivity.
//! Used by JobManager to run simulation in mylti-threaded mode.

class SpecularToySimulation
{
public:
    //! Represents results of the simulation.
    struct Result {
        double xmin{0.0};
        double xmax{5.0};
        std::vector<double> data;
    };

    SpecularToySimulation(const multislice_t& multislice);

    void runSimulation();

    void setProgressCallback(ModelView::ProgressHandler::callback_t callback);

    Result simulationResult() const;

    static Result sld_profile(const multislice_t& multislice, int n_points);

private:
    ModelView::ProgressHandler progress_handler;
    multislice_t input_data;
    Result specular_result;

    std::unique_ptr<SpecularScalarTanhStrategy> strategy;
};

#endif // DAREFL_QUICKSIMEDITOR_SPECULARTOYSIMULATION_H
