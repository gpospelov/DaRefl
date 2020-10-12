// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTDATASTRUCTURE_H
#define DAREFL_DATALOADER_IMPORTDATASTRUCTURE_H

#include <darefl/dataloader/importdatacolumn.h>
#include <darefl/dataloader/importutils.h>

#include <memory>
#include <string>
#include <vector>

namespace DataImportLogic
{

class DataColumn;

//! This will manage all the column objects
class DataStructure
{
public:
    DataStructure();
    ~DataStructure() = default;

    void setData(DataImportUtils::string_data& data);
    void setData(DataImportUtils::header_map& headers, DataImportUtils::string_data& data);

    DataColumn* column(const std::string& header);
    const DataColumn* column(int column) const;
    DataColumn* column(int column);

    int rowCount() const;
    int columnCount() const;

    void setColumnHistory(DataImportUtils::string_data history);
    DataImportUtils::string_data columnHistory() const;

private:
    void processHeaders(int num);
    void processHeaders(const std::vector<std::string>& headers);
    std::vector<bool> checkHeaders(const std::vector<std::string>& headers);
    void addColumn(const std::string& header);
    void delColumn(const std::string& header);
    void clearColumnValues();

private:
    std::vector<std::unique_ptr<DataColumn>> m_data_columns;
    DataImportUtils::string_data m_history;
};

} // end of namespace DataImportLogic

#endif // DAREFL_DATALOADER_IMPORTDATASTRUCTURE_H
