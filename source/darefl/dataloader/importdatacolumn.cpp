// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader/importdatacolumn.h>

#include <algorithm>
#include <cmath>
#include <functional>

namespace DataImportLogic
{

//! This is the constructor of DataColumn
DataColumn::DataColumn()
    : m_name("No Name"), m_type("Intensity"), m_header(""), m_unit("a.u."), m_multiplier(1.)
{
}

DataColumn::DataColumn(const std::string& header)
    : m_name("No Name"), m_type("Intensity"), m_header(header), m_unit("a.u."), m_multiplier(1.)
{
}

//! Setter for the values (str)
void DataColumn::setValues(const std::vector<std::string>& values)
{
    clearValues();
    for (const auto& value : values) {
        double value_double;
        try {
            value_double = std::stod(value);
        } catch (std::exception& e) {
            value_double = std::nan("");
        }
        m_values.push_back(value_double);
    }
}

//! Setter for the values (doubles)
void DataColumn::setValues(const std::vector<double>& values)
{
    m_values = values;
}

//! Clear the values int the column
void DataColumn::clearValues()
{
    m_values.clear();
}

//! Retrieve the current row count
int DataColumn::rowCount()
{
    return m_values.size();
}

//! Setter for the name
void DataColumn::setName(const std::string& name)
{
    m_name = name;
}

//! Setter for the type
void DataColumn::setType(const std::string& type)
{
    m_type = type;
}

//! Setter for the header
void DataColumn::setHeader(const std::string& header)
{
    m_header = header;
}

//! Setter for the units
void DataColumn::setUnit(const std::string& unit)
{
    m_unit = unit;
}

//! Setter for the multiplier
void DataColumn::setMultiplier(double multiplier)
{
    m_multiplier = multiplier;
}

//! Getter for the data values
std::vector<double> DataColumn::values() const
{
    return m_values;
}

//! Getter for the data values
std::vector<double> DataColumn::finalValues() const
{
    auto output = std::vector<double>(m_values);
    std::transform(output.begin(), output.end(), output.begin(),
                   [=](auto& c) { return c * multiplier(); });
    return output;
}

//! Getter for the data value at row
double DataColumn::value(int row) const
{
    return m_values.at(row);
}

//! Getter for the data value at row
double DataColumn::finalValue(int row) const
{
    return m_values.at(row) * multiplier();
}

//! Getter for the name
std::string DataColumn::name() const
{
    return m_name;
}

//! Getter for the type
std::string DataColumn::type() const
{
    return m_type;
}

//! Getter for the header
std::string DataColumn::header() const
{
    return m_header;
}

//! Getter for the unit
std::string DataColumn::unit() const
{
    return m_unit;
}

//! Getter for the multiplier
double DataColumn::multiplier() const
{
    return m_multiplier;
}

} // end of namespace DataImportLogic
