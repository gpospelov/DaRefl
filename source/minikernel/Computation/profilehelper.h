// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H
#define DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H

#include <utility>
#include <vector>
#include <minikernel/Computation/Slice.h>
#include <minikernel/Wrap/WinDllMacros.h>


//! Object that can generate the material profile of a sample as a function of depth.
namespace BornAgain
{

using multislice_t = std::vector<BornAgain::Slice>;

class MINIKERNEL_EXPORT ProfileHelper
{
public:
    ProfileHelper(const multislice_t& sample);
    ~ProfileHelper();

    std::vector<complex_t> calculateProfile(const std::vector<double>& z_values) const;
    std::pair<double, double> defaultLimits() const;

private:
    std::vector<complex_t> m_materialdata;
    std::vector<double> m_zlimits;
    std::vector<double> m_sigmas;
};

} // namespace BornAgain

#endif // DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H
