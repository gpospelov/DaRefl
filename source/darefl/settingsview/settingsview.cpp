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
#include <darefl/settingsview/settingsview.h>

SettingsView::SettingsView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_tabWidget(new QTabWidget), m_models(models)
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_tabWidget);
}

void SettingsView::init_tabs()
{

}
