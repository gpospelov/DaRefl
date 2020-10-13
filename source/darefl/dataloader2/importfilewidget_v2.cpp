// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QFileDialog>
#include <QListView>
#include <QStringListModel>
#include <QVBoxLayout>
#include <darefl/dataloader2/importfilewidget_v2.h>

ImportFileWidgetV2::ImportFileWidgetV2(QWidget* parent)
    : QWidget(parent), m_listView(new QListView), m_listModel(new QStringListModel)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_listView);

    m_listView->setModel(m_listModel);
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ImportFileWidgetV2::onAddFilesRequest() {}

void ImportFileWidgetV2::onRemoveFileRequest() {}
