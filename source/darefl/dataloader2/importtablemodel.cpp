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

//! Names of utility row on top of the table.
const QStringList utilityRowNames = {"Name", "Type", "Unit", "Multiplier"};

}; // namespace

ImportTableModelV2::ImportTableModelV2(QObject* parent) : QAbstractTableModel(parent) {}

int ImportTableModelV2::rowCount(const QModelIndex&) const
{
    return static_cast<int>(m_rawData.size()) + utilityRowCount();
}

int ImportTableModelV2::columnCount(const QModelIndex&) const
{
    return m_maxColumnCount;
}

QVariant ImportTableModelV2::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return dataFromIndex(index);

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

QVariant ImportTableModelV2::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    return section < utilityRowCount() ? utilityRowNames.at(section)
                                       : QVariant(section - utilityRowCount() + 1);
}

int ImportTableModelV2::utilityRowCount() const
{
    return utilityRowNames.size();
}

//! Returns data from index.

QVariant ImportTableModelV2::dataFromIndex(const QModelIndex& index) const
{
    int row = index.row() - utilityRowCount();
    if (row >= 0 && row < static_cast<int>(m_rawData.size())) {
        int col = index.column();
        if (col >= 0 && col < static_cast<int>(m_rawData[row].size())) {
            auto str = m_rawData[static_cast<int>(row)][static_cast<int>(col)];
            return QString::fromStdString(str);
        }
    }
    return QVariant();
}
