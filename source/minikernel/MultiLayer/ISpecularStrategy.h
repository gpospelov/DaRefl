// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISpecularStrategy.h
//! @brief     Defines and implements class ISpecularStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H

#include <minikernel/Computation/Slice.h>
#include <minikernel/MultiLayer/ILayerRTCoefficients.h>

//! Interface for the Fresnel computations, both in the scalar and magnetic case
//!
//! Inherited by SpecularScalarStrategy, SpecularMagneticOldStrategy,
//! SpecularMagneticStrategy, SpecularMagneticNewStrategy

//! @ingroup algorithms_internal

//! Interface for the Fresnel computations, both in the scalar and magnetic case
//!
//! Inherited by SpecularScalarStrategy, SpecularMagneticOldStrategy,
//! SpecularMagneticStrategy, SpecularMagneticNewStrategy

//! @ingroup algorithms_internal

class MINIKERNEL_EXPORT ISpecularStrategy
{
public:
    virtual ~ISpecularStrategy() = default;
    using single_coeff_t = std::unique_ptr<const ILayerRTCoefficients>;
    using coeffs_t = std::vector<single_coeff_t>;

    virtual coeffs_t Execute(const std::vector<BornAgain::Slice>& slices, const kvector_t& k) const = 0;

    virtual coeffs_t Execute(const std::vector<BornAgain::Slice>& slices,
                             const std::vector<complex_t>& kz) const = 0;
};

#endif // BORNAGAIN_CORE_MULTILAYER_ISPECULARSTRATEGY_H
