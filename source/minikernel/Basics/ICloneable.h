// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/ICloneable.h
//! @brief     Defines the standard mix-in ICloneable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_ICLONEABLE_H
#define BORNAGAIN_CORE_BASICS_ICLONEABLE_H

#include <minikernel/Wrap/WinDllMacros.h>

//! Interface for polymorphic classes that should not be copied, except by explicit cloning.
//!
//! Child classes of ICloneable must provide clone().

//! @ingroup tools_internal

class MINIKERNEL_EXPORT ICloneable
{
public:
    ICloneable();
    virtual ~ICloneable();

    ICloneable(const ICloneable&) = delete;
    ICloneable& operator=(const ICloneable&) = delete;

    virtual ICloneable* clone() const = 0;
    virtual void transferToCPP() {} //!< Used for Python overriding of clone (see swig/tweaks.py)
};

#endif // BORNAGAIN_CORE_BASICS_ICLONEABLE_H
