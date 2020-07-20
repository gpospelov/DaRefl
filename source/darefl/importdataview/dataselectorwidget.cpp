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
#include <mvvm/widgets/standardtreeviews.h>

DataSelectorWidget::DataSelectorWidget(DataViewModel* view_model, QWidget* parent)
    : QWidget(parent), m_viewModel(view_model),
      m_selectionModel(new DataSelectionModel(m_viewModel)), m_selectorTree(new QTreeView),
      m_canvasPropertyEditor(new ModelView::PropertyTreeView)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_selectorTree);
    layout->addWidget(m_canvasPropertyEditor);

    m_selectorTree->setModel(m_viewModel);
    m_selectorTree->setSelectionModel(m_selectionModel);
    m_selectorTree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_selectorTree->setDragDropMode(QAbstractItemView::InternalMove);
    m_selectorTree->setDragEnabled(true);

    connect(selectionModel(), &DataSelectionModel::selectionChanged, this,
            &DataSelectorWidget::onSelectionChanged);
}

DataSelectionModel* DataSelectorWidget::selectionModel() const
{
    return m_selectionModel;
}

void DataSelectorWidget::onSelectionChanged()
{

    selectionChanged(); // emmit further
}
