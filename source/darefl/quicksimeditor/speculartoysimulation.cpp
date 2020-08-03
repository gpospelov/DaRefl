// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <darefl/quicksimeditor/materialprofile.h>
#include <darefl/quicksimeditor/quicksimutils.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <minikernel/Computation/Slice.h>
#include <minikernel/MultiLayer/KzComputation.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/utils/containerutils.h>
#include <stdexcept>

namespace
{
const int simulation_points = 500;
} // namespace

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const multislice_t& multislice)
    : m_strategy(std::make_unique<SpecularScalarTanhStrategy>())
{
    m_inputData.sclice_data = multislice;
}

void SpecularToySimulation::runSimulation()
{
    auto slices = ::Utils::createBornAgainSlices(m_inputData.sclice_data);
    auto qvalues = ModelView::FixedBinAxisItem::create(simulation_points, m_specularResult.xmin,
                                                       m_specularResult.xmax)
                       ->binCenters();

    m_specularResult.data.reserve(simulation_points);

    m_progressHandler.reset();
    for (auto q : qvalues) {
        if (m_progressHandler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        auto kz = -0.5 * q;
        auto kzs = KzComputation::computeKzFromSLDs(slices, kz);
        auto coeff = std::move(m_strategy->Execute(slices, kzs).front());
        m_specularResult.data.emplace_back(std::norm(coeff->getScalarR()));

        m_progressHandler.setCompletedTicks(1);
    }
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    m_progressHandler.setMaxTicksCount(simulation_points);
    m_progressHandler.subscribe(callback);
}

SpecularToySimulation::Result SpecularToySimulation::simulationResult() const
{
    return m_specularResult;
}

SpecularToySimulation::Result SpecularToySimulation::sld_profile(const multislice_t& multislice,
                                                                 int n_points)
{
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(multislice);
    auto profile = MaterialProfile::CalculateProfile(multislice, n_points, xmin, xmax);
    return {xmin, xmax, ModelView::Utils::Real(profile)};
}
