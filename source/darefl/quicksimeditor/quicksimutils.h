// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H

#include <darefl/quicksimeditor/quicksim_types.h>

class MultiLayerItem;

namespace BornAgain
{
class Slice;
}

//! Collection of utility funcitons for running quick simulations.
namespace Utils
{

//! Creates multi-slice presentation of internal multilayer structure.
multislice_t CreateMultiSlice(const MultiLayerItem& multilayer);

std::vector<BornAgain::Slice> createBornAgainSlices(const multislice_t& multislice);

} // namespace Utils

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H
