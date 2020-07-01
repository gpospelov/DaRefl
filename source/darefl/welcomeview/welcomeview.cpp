// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QHBoxLayout>
#include <QMainWindow>
#include <darefl/model/applicationmodels.h>
#include <darefl/welcomeview/openprojectwidget.h>
#include <darefl/welcomeview/projecthandler.h>
#include <darefl/welcomeview/recentprojectsettings.h>
#include <darefl/welcomeview/recentprojectwidget.h>
#include <darefl/welcomeview/welcomeview.h>
#include <mvvm/project/projectutils.h>
#include <mvvm/widgets/widgetutils.h>

WelcomeView::WelcomeView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models), m_projectHandler(new ProjectHandler(models, this)),
      m_recent_project_widget(new RecentProjectWidget),
      m_open_project_widget(new OpenProjectWidget),
      m_settings(std::make_unique<RecentProjectSettings>())
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(palette);

    auto layout = new QHBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(m_recent_project_widget);
    layout->addWidget(m_open_project_widget);
    layout->addSpacing(50);

    setup_connections();
}

WelcomeView::~WelcomeView() = default;

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool WelcomeView::canCloseProject() const
{
    return m_projectHandler->canCloseProject();
}

void WelcomeView::updateNames()
{
    m_projectHandler->updateNames();
}

void WelcomeView::onCreateNewProject()
{
    m_projectHandler->onCreateNewProject();
}

void WelcomeView::onOpenExistingProject(const QString& dirname)
{
    return m_projectHandler->onOpenExistingProject(dirname);
}

void WelcomeView::onSaveCurrentProject()
{
    return m_projectHandler->onSaveCurrentProject();
}

void WelcomeView::onSaveProjectAs()
{
    return m_projectHandler->onSaveProjectAs();
}

void WelcomeView::setup_connections()
{
    // connect buttons of OpenProjectWidget with this slots.
    auto open_existing_project = [this]() { onOpenExistingProject(); };
    connect(m_open_project_widget, &OpenProjectWidget::openExistingProjectRequest,
            open_existing_project);
    connect(m_open_project_widget, &OpenProjectWidget::createNewProjectRequest, this,
            &WelcomeView::onCreateNewProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectRequest, this,
            &WelcomeView::onSaveCurrentProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectAsRequest, this,
            &WelcomeView::onSaveProjectAs);

    // connect RecentProjectWidget panels with this slots.
    connect(m_recent_project_widget, &RecentProjectWidget::projectSelected, this,
            &WelcomeView::onOpenExistingProject);

    // connect ProjectHandler with RecentProjectWidget
    connect(m_projectHandler, &ProjectHandler::currentProjectModified, m_recent_project_widget,
            &RecentProjectWidget::setCurrentProject);
    connect(m_projectHandler, &ProjectHandler::recentProjectsListModified, m_recent_project_widget,
            &RecentProjectWidget::setRecentProjectsList);
}
