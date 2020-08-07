// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/item_constants.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/standarditems/axisitems.h>

using namespace ModelView;

BasicSpecularScanItem::BasicSpecularScanItem(const std::string& model_type)
    : CompoundItem(model_type)
{
}

std::vector<double> BasicSpecularScanItem::qScanValues() const
{
    return {};
}

// ----------------------------------------------------------------------------

QSpecScanItem::QSpecScanItem() : BasicSpecularScanItem(::Constants::QSpecScanItemType)
{
    addProperty(P_NBINS, 500);
    addProperty(P_QMIN, 0.0);
    addProperty(P_QMAX, 1.0);
}

std::vector<double> QSpecScanItem::qScanValues() const
{
    int nbins = property<int>(P_NBINS);
    double qmin = property<double>(P_QMIN);
    double qmax = property<double>(P_QMAX);
    return FixedBinAxisItem::create(nbins, qmin, qmax)->binCenters();
}

// ----------------------------------------------------------------------------

ExperimentalScanItem::ExperimentalScanItem()
    : BasicSpecularScanItem(::Constants::ExperimentalScanItemType)
{
    addProperty(P_IMPORTED_DATA, ExternalProperty("Undefined", QColor(Qt::red)))
        ->setDisplayName("Graph");
}

// ----------------------------------------------------------------------------

SpecularScanGroupItem::SpecularScanGroupItem() : GroupItem(::Constants::SpecularScanGroupItemType)
{
    registerItem<QSpecScanItem>("Q-scan", /*make_selected*/ true);
    registerItem<ExperimentalScanItem>("Based on data");
    init_group();
}

// ----------------------------------------------------------------------------

SpecularBeamItem::SpecularBeamItem() : CompoundItem(::Constants::SpecularBeamItemType)
{
    addProperty(P_INTENSITY, 1.0)->setDisplayName("Intensity");
    addProperty<SpecularScanGroupItem>(P_SCAN_GROUP)->setDisplayName("Specular scan type");
}

std::vector<double> SpecularBeamItem::qScanValues() const
{
    auto scan_group = item<SpecularScanGroupItem>(P_SCAN_GROUP);
    if (auto scanItem = dynamic_cast<const BasicSpecularScanItem*>(scan_group->currentItem());
        scanItem)
        return scanItem->qScanValues();
    return {};
}

// ----------------------------------------------------------------------------

SpecularInstrumentItem::SpecularInstrumentItem()
    : CompoundItem(::Constants::SpecularInstrumentItemType)
{
    addProperty<SpecularBeamItem>(P_BEAM);
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const
{
    return item<SpecularBeamItem>(P_BEAM);
}
