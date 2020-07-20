// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/dataselectorwidget.h>
#include <darefl/importdataview/dataviewmodel.h>

DataSelectorWidget::DataSelectorWidget(DataViewModel* view_model,
                                       DataSelectionModel* selection_model, QWidget* parent)
    : QWidget(parent), m_viewModel(view_model), m_selectionModel(selection_model),
      m_selectorTree(new QTreeView)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_selectorTree);

    m_selectorTree->setModel(m_viewModel);
    m_selectorTree->setSelectionModel(m_selectionModel);
    m_selectorTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_selectorTree->setDragDropMode(QAbstractItemView::InternalMove);
    m_selectorTree->setDragEnabled(true);
}
