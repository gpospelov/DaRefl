// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/dataloader_types.h>
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

std::vector<QVariant> CreateMultiplierVariants(int maxColumnCount)
{
    std::vector<QVariant> result(maxColumnCount, 1.0);
    return result;
}

std::vector<QVariant> CreateNameVariants(int maxColumnCount)
{
    std::vector<QVariant> result(maxColumnCount, QString(""));
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

QVariant ImportTableHeader::data(int row, int column) const
{
    return isValid(row, column) ? m_data[row][column] : QVariant();
}

bool ImportTableHeader::setData(int row, int column, const QVariant& variant)
{
    if (isValid(row, column)) {
        m_data[row][column] = variant;
        return true;
    }

    return false;
}

std::string ImportTableHeader::rowName(int row) const
{
    return utilityRowNames[row];
}

DataLoader::ColumnInfo ImportTableHeader::columnInfo(int column) const
{
    if (column < 0 || column >= columnCount())
        return {};

    DataLoader::ColumnInfo result;
    result.column = column;
    result.type_name = data(TYPE, column).value<ComboProperty>().currentIndex();
    result.units = data(UNITS, column).value<ComboProperty>().currentIndex();
    result.multiplier = data(UNITS, column).value<double>();
    result.title = data(TITLE, column).toString().toStdString();

    return result;
}

//! Returns vector of info objects describing x,y axes construction.

// std::vector<ImportTableHeader::axes_info_t> ImportTableHeader::axesInfo() const
//{
//    return {};
//}

////! Returns info for all columns with given type_name set.

// std::vector<DataLoader::ColumnInfo> ImportTableHeader::infoForType(const std::string& type_name)
// const
//{
//    std::vector<DataLoader::ColumnInfo> result;

//    return result;
//}

void ImportTableHeader::init_data()
{
    m_data.push_back(CreateTypeVariants(columnCount()));
    m_data.push_back(CreateUnitVariants(columnCount()));
    m_data.push_back(CreateMultiplierVariants(columnCount()));
    m_data.push_back(CreateNameVariants(columnCount()));
}

//! Returns true if given pair of indices are valid for data array.

bool ImportTableHeader::isValid(int row, int column) const
{
    return (row >= 0 && row < static_cast<int>(m_data.size()))
           && (column >= 0 && column < static_cast<int>(m_data[row].size()));
}
