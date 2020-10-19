// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_IMPORTTABLEHEADER_H
#define DAREFL_DATALOADER2_IMPORTTABLEMODEL_H

#include <QVariant>
#include <vector>

//!

class ImportTableHeader
{
public:
    using header_data_t = std::vector<std::vector<QVariant>>;

    ImportTableHeader(int max_column_count);

    int rowCount() const;

    int columnCount() const;
private:
    void init_data();

    header_data_t m_data;
    int m_maxColumnCount;
};

#endif // DAREFL_DATALOADER2_IMPORTTABLEMODEL_H
