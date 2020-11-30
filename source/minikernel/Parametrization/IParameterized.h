// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameterized.h
//! @brief     Defines class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETERIZED_H
#define BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETERIZED_H

#include <minikernel/Basics/BornAgainNamespace.h>
#include <minikernel/Basics/INamed.h>
#include <minikernel/Vector/Vectors3D.h>

class RealLimits;
class ParameterPool;
class RealParameter;

//! Manages a local parameter pool, and a tree of child pools.
//! @ingroup tools_internal

class MINIKERNEL_EXPORT IParameterized : public INamed
{
public:
    IParameterized(const std::string& name = "");
    IParameterized(const IParameterized& other);
    ~IParameterized();

    IParameterized& operator=(const IParameterized& other) = delete;

    //! Returns pointer to the parameter pool.
    ParameterPool* parameterPool() const { return m_pool; }

    //! Creates new parameter pool, with all local parameters and those of its children.
    virtual ParameterPool* createParameterTree() const;

    //! Returns multiline string representing available parameters.
    std::string parametersToString() const;

//    RealParameter& registerParameter(const std::string& name, double* parpointer);

    void registerVector(const std::string& base_name, kvector_t* p_vec,
                        const std::string& units = BornAgain::UnitsNm);

    void setParameterValue(const std::string& name, double value);

    void setVectorValue(const std::string& base_name, kvector_t value);

    RealParameter* parameter(const std::string& name) const;

    //! Action to be taken in inherited class when a parameter has changed.
    virtual void onChange() {}

    void removeParameter(const std::string& name);

    void removeVector(const std::string& base_name);

    static std::string XComponentName(const std::string& base_name);
    static std::string YComponentName(const std::string& base_name);
    static std::string ZComponentName(const std::string& base_name);

private:
    ParameterPool* m_pool; //!< parameter pool (kind of pointer-to-implementation)
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_IPARAMETERIZED_H
