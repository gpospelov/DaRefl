// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Slice.h
//! @brief     Defines class Slice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SLICE_H
#define SLICE_H

#include <minikernel/Material/Material.h>
#include <minikernel/Wrap/WinDllMacros.h>
#include <minikernel/Basics/MathConstants.h>
#include <memory>

class LayerRoughness;

namespace BornAgain {

//! Data structure containing the data of a single slice, for calculating the Fresnel coefficients.
//!
//! @ingroup algorithms_internal

class MINIKERNEL_EXPORT Slice
{
public:
    Slice(double thickness, const Material& material);
    Slice(double thickness, const Material& material, const LayerRoughness& top_roughness);
    Slice(const Slice& other);
    Slice(Slice&& other);
    Slice& operator=(const Slice& other);
    ~Slice();

    void setMaterial(const Material& material);
    Material material() const;

    double thickness() const;
    const LayerRoughness* topRoughness() const;

    //! Return the potential term that is used in the one-dimensional Fresnel calculations
    complex_t scalarReducedPotential(kvector_t k, double n_ref) const;

#ifndef SWIG
    //! Return the potential term that is used in the one-dimensional Fresnel calculations
    //! in the presence of magnetization
    Eigen::Matrix2cd polarizedReducedPotential(kvector_t k, double n_ref) const;
#endif

    //! Initializes the magnetic B field from a given ambient field strength H
    void initBField(kvector_t h_field, double b_z);
    kvector_t bField() const { return m_B_field; }

    void invertBField();

    static constexpr double Magnetic_Permeability = 4e-7 * M_PI;

private:
    double m_thickness;
    Material m_material;
    kvector_t m_B_field; //!< cached value of magnetic induction
    std::unique_ptr<LayerRoughness> mP_top_roughness;
};

} // namespace BornAgain

#endif // SLICE_H
