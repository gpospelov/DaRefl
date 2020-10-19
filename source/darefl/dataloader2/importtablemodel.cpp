// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/importtablemodel.h>
#include <mvvm/model/comboproperty.h>

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
const std::vector<std::string> utilityRowNames = {"Type", "Unit", "Multiplier", "Name"};

const std::vector<std::string> typeNames = {"Axis", "Intensity", "Ignore"};

const std::vector<std::string> unitNames = {"a.u.", "counts", "1/nm", "Angstrom"};

using ModelView::ComboProperty;

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
    initHeaderData();
    endResetModel();
}

QVariant ImportTableModelV2::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    return section < utilityRowCount() ? QString::fromStdString(utilityRowNames.at(section))
                                       : QVariant(section - utilityRowCount() + 1);
}

void ImportTableModelV2::initHeaderData()
{
    m_headerData.clear();
    m_headerData.push_back(CreateTypeVariants(columnCount()));
    m_headerData.push_back(CreateUnitVariants(columnCount()));
    m_headerData.push_back(CreateMultiplayerVariants(columnCount()));
    m_headerData.push_back(CreateNameVariants(columnCount()));
}

int ImportTableModelV2::utilityRowCount() const
{
    return utilityRowNames.size();
}

//! Returns data from index. Combines header data with parsed user data.

QVariant ImportTableModelV2::dataFromIndex(const QModelIndex& index) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < utilityRowCount()) {
        return m_headerData[index.row()][index.column()];

    } else {
        int row = index.row() - utilityRowCount();
        if (row >= 0 && row < static_cast<int>(m_rawData.size())) {
            int col = index.column();
            if (col >= 0 && col < static_cast<int>(m_rawData[row].size())) {
                auto str = m_rawData[static_cast<int>(row)][static_cast<int>(col)];
                return QString::fromStdString(str);
            }
        }
    }
    return QVariant();
}
