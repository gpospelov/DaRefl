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
#include <darefl/dataloader2/importtablewidget.h>

ImportTableWidget::ImportTableWidget(QWidget* parent)
    : QWidget(parent), m_model(new QStandardItemModel), m_tableView(new QTableView)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tableView);
}
