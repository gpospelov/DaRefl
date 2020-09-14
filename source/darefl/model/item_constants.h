// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_ITEM_CONSTANTS_H
#define DAREFL_MODEL_ITEM_CONSTANTS_H

#include <string>

namespace Constants
{

const std::string MultiLayerItemType = "MultiLayer";
const std::string LayerItemType = "Layer";
const std::string RoughnessItemType = "Roughness";
const std::string SLDMaterialItemType = "SLDMaterial";
const std::string MaterialContainerItemType = "MaterialContainer";
const std::string JobItemType = "Job";
const std::string CanvasItemType = "Canvas";
const std::string SLDCanvasItemType = "SLDCanvas";
const std::string CanvasContainerItemType = "CanvasContainer";
const std::string RawDataMimeType = "quickrefl/moveDataItem";
const std::string ExperimentalDataContainerItemType = "ExperimentalDataContainer";
const std::string SpecularInstrumentItemType = "SpecularInstrument";
const std::string SpecularBeamItemType = "SpecularBeam";
const std::string SpecularScanGroupItemType = "SpecularScanGroup";
const std::string QSpecScanItemType = "QSpecScan";
const std::string ExperimentalScanItemType = "ExperimentalScan";

} // namespace Constants

#endif // DAREFL_MODEL_ITEM_CONSTANTS_H
