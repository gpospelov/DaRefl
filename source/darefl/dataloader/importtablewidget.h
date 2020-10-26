// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTTABLEWIDGET_H
#define DAREFL_DATALOADER_IMPORTTABLEWIDGET_H

#include <QWidget>
#include <string>
#include <vector>
#include <memory>

namespace ModelView
{
class ViewModelDelegate;
}

namespace DataLoader
{
struct ColumnInfo;
}

class QTableView;
class ImportTableModel;

//! Contains table with imported data.
//! Belongs to LoaderPreviewPanel.

class ImportTableWidget : public QWidget
{
    Q_OBJECT

public:
    ImportTableWidget(QWidget* parent = nullptr);
    ~ImportTableWidget();

    void setRawData(const std::vector<std::vector<std::string>>& table_data);

    std::vector<DataLoader::ColumnInfo> columnInfo() const;

private:
    ImportTableModel* m_tableModel{nullptr};
    QTableView* m_tableView{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // DAREFL_DATALOADER_IMPORTTABLEWIDGET_H