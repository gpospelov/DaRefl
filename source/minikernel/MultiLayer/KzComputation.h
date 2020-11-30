// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/KzComputation.h
//! @brief     Declares functions from KzComputation namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_KZCOMPUTATION_H
#define BORNAGAIN_CORE_MULTILAYER_KZCOMPUTATION_H

#include <minikernel/Basics/Complex.h>
#include <minikernel/Basics/ICloneable.h>
#include <minikernel/Vector/Vectors3D.h>
#include <vector>

namespace BornAgain
{
class Slice;
}

//! Namespace containing functions for computing kz values for given multilayer and k (or kz) value
//! on the surface of the sample.
//! @ingroup samples_internal

namespace KzComputation
{
/* Computes kz values from known k vector and slices with the following assumptions:
 * - the beam penetrates fronting medium from a side
 * - the wavelength is known for a distant point in vacuum (ref. index = 1)
 * - the incident angle is known for the sample surface
 *
 * This function is used in GISAS and off-spec computations mainly for back-compatibility
 * reasons and should be replaced with computeKzFromRefIndices.
 */
MINIKERNEL_EXPORT std::vector<complex_t> computeReducedKz(const std::vector<BornAgain::Slice>& slices, kvector_t k);

/* Computes kz values from kz of the incoming beam known at a distant point in vacuum.
 * It is assumed, that the beam penetrates fronting medium from a side.
 */
MINIKERNEL_EXPORT std::vector<complex_t> computeKzFromSLDs(const std::vector<BornAgain::Slice>& slices, double kz);

/* Computes kz values from k-vector of the incoming beam known at a distant point in vacuum.
 * It is assumed, that the beam penetrates fronting medium from a side.
 */
MINIKERNEL_EXPORT std::vector<complex_t> computeKzFromRefIndices(const std::vector<BornAgain::Slice>& slices,
                                                            kvector_t k);
} // namespace KzComputation

#endif // BORNAGAIN_CORE_MULTILAYER_KZCOMPUTATION_H
