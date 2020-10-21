// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_IMPORTTABLEMODEL_H
#define DAREFL_DATALOADER2_IMPORTTABLEMODEL_H

#include <QAbstractTableModel>
#include <string>
#include <vector>
#include <memory>

class ImportTableHeader;

//! Table model to hold imported ASCII data after parsing it to multi-column presentation.

class ImportTableModelV2 : public QAbstractTableModel
{
    Q_OBJECT

public:
    using raw_data_t = std::vector<std::vector<std::string>>;

    ImportTableModelV2(QObject* parent = nullptr);
    ~ImportTableModelV2() override;

    int rowCount(const QModelIndex& = QModelIndex()) const override;

    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setRawData(const raw_data_t& raw_data);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    int utilityRowCount() const;
    QVariant dataFromIndex(const QModelIndex& index) const;

    std::unique_ptr<ImportTableHeader> m_header;
    raw_data_t m_rawData; //! parsed column data

    int m_maxColumnCount{0};
};

#endif // DAREFL_DATALOADER2_IMPORTTABLEMODEL_H
