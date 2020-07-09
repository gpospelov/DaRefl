// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QTabWidget>
#include <QTreeView>
#include <darefl/model/applicationmodels.h>
#include <darefl/settingsview/settingsview.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/widgets/allitemstreeview.h>

SettingsView::SettingsView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_tabWidget(new QTabWidget), m_models(models)
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_tabWidget);
    init_tabs();
}

//! Initialize tabs with model content.
//! Each model will be represented by a single tree (with all items shown) in a tab.

void SettingsView::init_tabs()
{
    for (auto model : m_models->application_models()) {
        auto view = new ModelView::AllItemsTreeView(model);
        view->treeView()->setAlternatingRowColors(true);
        m_tabWidget->addTab(view, QString::fromStdString(model->modelType()));
    }
}
