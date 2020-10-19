// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/importtableheader.h>

namespace
{
const std::vector<std::string> utilityRowNames = {"Type", "Unit", "Multiplier", "Name"};

const std::vector<std::string> typeNames = {"Axis", "Intensity", "Ignore"};

const std::vector<std::string> unitNames = {"a.u.", "counts", "1/nm", "Angstrom"};
} // namespace

ImportTableHeader::ImportTableHeader(int max_column_count) : m_maxColumnCount(max_column_count) {}

int ImportTableHeader::rowCount() const
{
    return utilityRowNames.size();
}

int ImportTableHeader::columnCount() const
{
    return m_maxColumnCount;
}

void ImportTableHeader::init_data()
{
    m_data.clear();
//    m_data.push_back(CreateTypeVariants(columnCount()));
//    m_data.push_back(CreateUnitVariants(columnCount()));
//    m_data.push_back(CreateMultiplayerVariants(columnCount()));
//    m_data.push_back(CreateNameVariants(columnCount()));
}
