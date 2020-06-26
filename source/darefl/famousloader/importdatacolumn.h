// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTDATACOLUMN_H
#define DAREFL_FAMOUSLOADER_IMPORTDATACOLUMN_H

#include <darefl/famousloader/importutils.h>

#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

//! This is the column object for the data
class DataColumn
{
public:
    DataColumn();
    DataColumn(const std::string& header);
    ~DataColumn() = default;

    void setValues(const std::vector<std::string>& values);
    void setValues(const std::vector<double>& values);
    void clearValues();
    int rowCount();

    void setName(const std::string& name);
    void setType(const std::string& type);
    void setHeader(const std::string& header);
    void setUnit(const std::string& unit);
    void setMultiplier(double multiplier);

    std::vector<double> values() const;
    std::vector<double> finalValues() const;
    double value(int row) const;
    double finalValue(int row) const;
    std::string name() const;
    std::string type() const;
    std::string header() const;
    std::string unit() const;
    double multiplier() const;

private:
    std::string m_name;
    std::string m_type;
    std::string m_header;
    std::string m_unit;
    double m_multiplier;
    std::vector<double> m_values;
};

} // end of namespace DataImportLogic

#endif // DAREFL_FAMOUSLOADER_IMPORTDATACOLUMN_H
