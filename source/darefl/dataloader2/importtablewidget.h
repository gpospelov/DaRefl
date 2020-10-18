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

class QTableView;
class QStandardItemModel;

//! Contains table with imported data.
//! Belongs to LoaderPreviewPanel.

class ImportTableWidget : public QWidget
{
    Q_OBJECT

public:
    ImportTableWidget(QWidget* parent = nullptr);

private:
    QStandardItemModel* m_model{nullptr};
    QTableView* m_tableView{nullptr};
};

#endif // DAREFL_DATALOADER2_IMPORTDATVLEWIDGET_H
