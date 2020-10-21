// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/importtableheader.h>
#include <mvvm/model/comboproperty.h>

using ModelView::ComboProperty;

namespace
{
const std::vector<std::string> utilityRowNames = {"Type", "Unit", "Multiplier", "Name"};

const std::vector<std::string> typeNames = {"Axis", "Intensity", "Ignore"};

const std::vector<std::string> unitNames = {"a.u.", "counts", "1/nm", "Angstrom"};

QVariant CreateTypeVariant(int col = 0)
{
    auto combo = ComboProperty::createFrom(typeNames);
    auto selected_value = col == 0 ? typeNames[0] : typeNames[1];
    combo.setValue(selected_value);
    return QVariant::fromValue<ComboProperty>(combo);
}

std::vector<QVariant> CreateTypeVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(CreateTypeVariant(i));
    return result;
}

std::vector<QVariant> CreateUnitVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(QVariant::fromValue<ComboProperty>(ComboProperty::createFrom(unitNames)));
    return result;
}

std::vector<QVariant> CreateMultiplayerVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(QVariant::fromValue<double>(1.0));
    return result;
}

std::vector<QVariant> CreateNameVariants(int maxColumnCount)
{
    std::vector<QVariant> result;
    for (int i = 0; i < maxColumnCount; ++i)
        result.push_back(QString(""));
    return result;
}

} // namespace

ImportTableHeader::ImportTableHeader(int max_column_count) : m_maxColumnCount(max_column_count)
{
    init_data();
}

int ImportTableHeader::rowCount() const
{
    return utilityRowNames.size();
}

int ImportTableHeader::columnCount() const
{
    return m_maxColumnCount;
}

QVariant ImportTableHeader::data(int row, int col) const
{
    if (row >= 0 && row < static_cast<int>(m_data.size()))
        if (col >= 0 && col < static_cast<int>(m_data[row].size()))
            return m_data[row][col];
    return QVariant();
}

void ImportTableHeader::setData(const QVariant& variant, int row, int col)
{
    if (row >= 0 && row < static_cast<int>(m_data.size()))
        if (col >= 0 && col < static_cast<int>(m_data[row].size()))
            m_data[row][col] = variant;
}

std::string ImportTableHeader::rowName(int row) const
{
    return utilityRowNames[row];
}

void ImportTableHeader::init_data()
{
    m_data.push_back(CreateTypeVariants(columnCount()));
    m_data.push_back(CreateUnitVariants(columnCount()));
    m_data.push_back(CreateMultiplayerVariants(columnCount()));
    m_data.push_back(CreateNameVariants(columnCount()));
}
