// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIM_TYPES_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIM_TYPES_H

#include <complex>
#include <vector>

using complex_t = std::complex<double>;

//! Data structure for simple multilayer representation.

struct Slice {
    complex_t material;
    double thickness{0.0};
    double sigma{0.0}; // top interface sigma
};
using multislice_t = std::vector<Slice>;

//! Represents data to run specular simulations.

struct SimulationInput {
    std::vector<double> qvalues;
    multislice_t slice_data;
    double intensity;
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIM_TYPES_H
