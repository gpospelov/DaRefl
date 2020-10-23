// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_IMPORTTABLEHEADER_H
#define DAREFL_DATALOADER2_IMPORTTABLEHEADER_H

#include <QVariant>
#include <vector>

namespace DataLoader
{
struct ColumnInfo;
}

//! Holds all data related to the content of utility rows in ImportTableModel.

class ImportTableHeader
{
public:
    enum RowTypes {TYPE, UNITS, MULTIPLIER, TITLE, MAX};
    using header_data_t = std::vector<std::vector<QVariant>>;

    ImportTableHeader(int max_column_count);

    int rowCount() const;

    int columnCount() const;

    QVariant data(int row, int column) const;

    bool setData(int row, int column, const QVariant& variant);

    std::string rowName(int row) const;

    std::vector<DataLoader::ColumnInfo> columnInfo() const;

private:
    void init_data();
    bool isValid(int row, int column) const;

    header_data_t m_data;
    int m_maxColumnCount;
};

#endif // DAREFL_DATALOADER2_IMPORTTABLEHEADER_H
