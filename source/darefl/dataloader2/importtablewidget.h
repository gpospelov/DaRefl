// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_IMPORTDATVLEWIDGET_H
#define DAREFL_DATALOADER2_IMPORTDATVLEWIDGET_H

#include <QWidget>
#include <string>
#include <vector>

class QTableView;
class QStandardItemModel;
class ImportTableModelV2;

//! Contains table with imported data.
//! Belongs to LoaderPreviewPanel.

class ImportTableWidget : public QWidget
{
    Q_OBJECT

public:
    ImportTableWidget(QWidget* parent = nullptr);

    void setRawData(const std::vector<std::vector<std::string>>& table_data);

private:
    ImportTableModelV2* m_tableModel{nullptr};
    QTableView* m_tableView{nullptr};
};

#endif // DAREFL_DATALOADER2_IMPORTDATVLEWIDGET_H
