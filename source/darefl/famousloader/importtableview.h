// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTTABLEVIEW_H
#define DAREFL_FAMOUSLOADER_IMPORTTABLEVIEW_H

#include <darefl/famousloader/importdatastructure.h>
#include <darefl/famousloader/importutils.h>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QStyledItemDelegate>
#include <QTableView>
#include <vector>

namespace DataImportGui
{

// -------------------------------------------------
// This is the area for the table model
class ImportTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ImportTableModel(QWidget* parent = nullptr);

    void setDataStructure(DataImportLogic::DataStructure* data_structure);
    DataImportLogic::DataStructure* dataStructure() const;
    void refreshFromDataStructure();

    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int numUtilityRows() const;
    std::vector<DataImportUtils::InfoTypes> infoTypes() const;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;

    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    DataImportLogic::DataStructure* p_data_structure{nullptr};
    bool m_show_name;
    bool m_show_type;
    bool m_show_header;
    bool m_show_units;
    bool m_show_multiplier;
};

// -------------------------------------------------
// This is the area for the table view delegate
class ImportTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ImportTableDelegate(QObject* parent = nullptr);
    ~ImportTableDelegate();

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;
};

// -------------------------------------------------
// This is the area for the table view
class ImportTableView : public QTableView
{
    Q_OBJECT

public:
    ImportTableView(QWidget* parent = nullptr);
    ImportTableModel* model() const;
};

} // End of namespace DataImportGui

#endif  // DAREFL_FAMOUSLOADER_IMPORTTABLEVIEW_H
