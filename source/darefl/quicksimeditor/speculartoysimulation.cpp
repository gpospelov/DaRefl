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
#include <minikernel/MultiLayer/SpecularScalarTanhStrategy.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/utils/containerutils.h>
#include <stdexcept>

using namespace ModelView;

SpecularToySimulation::~SpecularToySimulation() = default;

SpecularToySimulation::SpecularToySimulation(const InputData& input_data)
    : m_inputData(input_data), m_strategy(std::make_unique<SpecularScalarTanhStrategy>())
{
}

void SpecularToySimulation::runSimulation()
{
    auto slices = ::Utils::createBornAgainSlices(m_inputData.slice_data);

    m_specularResult.amplitudes.reserve(scanPointsCount());

    m_progressHandler.reset();
    for (auto q : m_inputData.qvalues) {
        if (m_progressHandler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        auto kz = -0.5 * q;
        auto kzs = KzComputation::computeKzFromSLDs(slices, kz);
        auto coeff = std::move(m_strategy->Execute(slices, kzs).front());
        auto amplitude = std::norm(coeff->getScalarR()) * m_inputData.intensity;
        m_specularResult.amplitudes.emplace_back(amplitude);

        m_progressHandler.setCompletedTicks(1);
    }
    m_specularResult.qvalues = m_inputData.qvalues;
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    m_progressHandler.setMaxTicksCount(scanPointsCount());
    m_progressHandler.subscribe(callback);
}

SpecularToySimulation::Result SpecularToySimulation::simulationResult() const
{
    return m_specularResult;
}

SpecularToySimulation::sld_profile_t
SpecularToySimulation::sld_profile(const multislice_t& multislice, int n_points)
{
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(multislice);
    auto profile = MaterialProfile::CalculateProfile(multislice, n_points, xmin, xmax);
    return {xmin, xmax, ModelView::Utils::Real(profile)};
}

size_t SpecularToySimulation::scanPointsCount() const
{
    return m_inputData.qvalues.size();
}
