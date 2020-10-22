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
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/importtablemodel.h>
#include <darefl/dataloader2/importtablewidget.h>
#include <mvvm/editors/combopropertyeditor.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

ImportTableWidget::ImportTableWidget(QWidget* parent)
    : QWidget(parent), m_tableModel(new ImportTableModelV2), m_tableView(new QTableView),
      m_delegate(new ModelView::ViewModelDelegate)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tableView);

    m_tableView->setItemDelegate(m_delegate.get());
    m_tableView->setModel(m_tableModel);
}

ImportTableWidget::~ImportTableWidget() = default;

void ImportTableWidget::setRawData(const std::vector<std::vector<std::string>>& table_data)
{
    m_tableModel->setRawData(table_data);
}

std::vector<DataLoader::ColumnInfo> ImportTableWidget::columnInfo() const
{
    return m_tableModel->columnInfo();
}
