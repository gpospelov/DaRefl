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

#include <darefl/quicksimeditor/slice.h>
class MultiLayerItem;

//! Collection of utility funcitons for running quick simulations.
namespace Utils
{

//! Creates multi-slice presentation of internal multilayer structure.
multislice_t CreateMultiSlice(const MultiLayerItem& multilayer);

} // namespace Utils

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H
