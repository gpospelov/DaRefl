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
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/editors/combopropertyeditor.h>
#include <mvvm/model/comboproperty.h>
#include <QItemEditorFactory>
#include <QStandardItemEditorCreator>
#include <QStyledItemDelegate>

ImportTableWidget::ImportTableWidget(QWidget* parent)
    : QWidget(parent), m_tableModel(new ImportTableModelV2), m_tableView(new QTableView),
      m_delegate(new ModelView::ViewModelDelegate), m_styledDelegate(new QStyledItemDelegate(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_tableView);

//    m_tableView->setItemDelegate(m_delegate.get());

    QItemEditorFactory *factory = new QItemEditorFactory;

    QItemEditorCreatorBase *colorListCreator =
        new QStandardItemEditorCreator<ModelView::ComboPropertyEditor>();


    ModelView::ComboProperty combo;
    factory->registerEditor(QVariant::fromValue(combo).userType(), colorListCreator);

    m_styledDelegate->setItemEditorFactory(factory);
    m_tableView->setItemDelegate(m_styledDelegate);


//   m_tableView->itemDelegate()->setItemE


    m_tableView->setModel(m_tableModel);
}

ImportTableWidget::~ImportTableWidget() = default;

void ImportTableWidget::setRawData(const std::vector<std::vector<std::string>>& table_data)
{
    m_tableModel->setRawData(table_data);
}
