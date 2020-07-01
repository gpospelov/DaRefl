// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QMainWindow>
#include <darefl/model/applicationmodels.h>
#include <darefl/welcomeview/openprojectwidget.h>
#include <darefl/welcomeview/recentprojectwidget.h>
#include <darefl/welcomeview/welcomeview2.h>
#include <darefl/welcomeview/welcomeviewsettings.h>
#include <mvvm/project/projectutils.h>
#include <mvvm/widgets/widgetutils.h>

WelcomeView2::WelcomeView2(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models), m_recent_project_widget(new RecentProjectWidget),
      m_open_project_widget(new OpenProjectWidget),
      m_settings(std::make_unique<WelcomeViewSettings>())
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

WelcomeView2::~WelcomeView2() = default;

//! Returns 'true' if current project can be closed.
//! Internally will perform check for unsaved data, and proceed via save/discard/cancel dialog.

bool WelcomeView2::canCloseProject() const
{
    return false;
//    return m_project_manager->closeCurrentProject();
}

void WelcomeView2::onCreateNewProject()
{
    qDebug() << "WelcomeView::onCreateNewProject()";
}

void WelcomeView2::onOpenExistingProject(const QString& dirname)
{
    qDebug() << "WelcomeView::onOpenExistingProject()" << dirname;
}

void WelcomeView2::onSaveCurrentProject()
{
    qDebug() << "WelcomeView::onSaveCurrentProject()";
}

void WelcomeView2::onSaveProjectAs()
{
    qDebug() << "WelcomeView::onSaveProjectAs()";
}

void WelcomeView2::setup_connections()
{
    auto open_existing_project = [this]() { onOpenExistingProject(); };
    connect(m_open_project_widget, &OpenProjectWidget::openExistingProjectRequest,
            open_existing_project);
    connect(m_open_project_widget, &OpenProjectWidget::createNewProjectRequest, this,
            &WelcomeView2::onCreateNewProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectRequest, this,
            &WelcomeView2::onSaveCurrentProject);
    connect(m_open_project_widget, &OpenProjectWidget::saveProjectAsRequest, this,
            &WelcomeView2::onSaveProjectAs);
    connect(m_recent_project_widget, &RecentProjectWidget::projectSelected, this,
            &WelcomeView2::onOpenExistingProject);
}

