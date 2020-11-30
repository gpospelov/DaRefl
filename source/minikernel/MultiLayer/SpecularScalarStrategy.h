// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarStrategy.h
//! @brief     Defines class SpecularScalarStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARSTRATEGY_H

#include <minikernel/MultiLayer/ISpecularStrategy.h>
#include <minikernel/MultiLayer/ScalarRTCoefficients.h>
#include <minikernel/Vector/Vectors3D.h>
#include <memory>
#include <vector>

namespace BornAgain {
class Slice;
}

//! Implements the scalar Fresnel computation
//!
//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//!
//! Inherited by SpecularScalarNCStrategy, SpecularScalarTanhStrategy
//!
//! @ingroup algorithms_internal
class MINIKERNEL_EXPORT SpecularScalarStrategy : public ISpecularStrategy
{
public:
    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    virtual ISpecularStrategy::coeffs_t Execute(const std::vector<BornAgain::Slice>& slices,
                                                const kvector_t& k) const override;

    virtual ISpecularStrategy::coeffs_t Execute(const std::vector<BornAgain::Slice>& slices,
                                                const std::vector<complex_t>& kz) const override;

private:
    virtual Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma,
                                        double thickness, const Eigen::Vector2cd& t_r1) const = 0;

    std::vector<ScalarRTCoefficients> computeTR(const std::vector<BornAgain::Slice>& slices,
                                                const std::vector<complex_t>& kz) const;

    static void setZeroBelow(std::vector<ScalarRTCoefficients>& coeff, size_t current_layer);

    bool calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                              const std::vector<BornAgain::Slice>& slices, const std::vector<complex_t>& kz,
                              size_t slice_index) const;
};

#endif // BORNAGAIN_CORE_MULTILAYER_SPECULARSCALARSTRATEGY_H
