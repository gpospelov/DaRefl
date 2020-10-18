// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/importtablemodel.h>

namespace
{
//! Returns maximum number of columns in 2D data vector.
int maxColumnCount(const ImportTableModelV2::raw_data_t& data)
{
    int result{0};
    for (const auto& x : data)
        result = std::max(result, static_cast<int>(x.size()));
    return result;
}

} // namespace

ImportTableModelV2::ImportTableModelV2(QObject* parent) : QAbstractTableModel(parent) {}

int ImportTableModelV2::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_rawData.size());
}

int ImportTableModelV2::columnCount(const QModelIndex&) const
{
    return m_maxColumnCount;
}

QVariant ImportTableModelV2::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() <= static_cast<int>(m_rawData[index.row()].size())) {
            auto str = m_rawData[static_cast<int>(index.row())][static_cast<int>(index.column())];
            return QString::fromStdString(str);
        }
    }

    return QVariant();
}

//! Sets content of the model.

void ImportTableModelV2::setRawData(const ImportTableModelV2::raw_data_t& raw_data)
{
    beginResetModel();
    m_rawData = raw_data;
    m_maxColumnCount = maxColumnCount(m_rawData);
    endResetModel();
}
