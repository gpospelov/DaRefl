// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <darefl/dataloader2/importtablemodel.h>
#include <darefl/dataloader2/importtablewidget.h>

ImportTableWidget::ImportTableWidget(QWidget* parent)
    : QWidget(parent), m_tableModel(new ImportTableModelV2), m_tableView(new QTableView)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tableView);

    m_tableView->setModel(m_tableModel);
}

void ImportTableWidget::setData(const std::vector<std::vector<std::string>>& table_data)
{
    m_tableModel->setRawData(table_data);
}
