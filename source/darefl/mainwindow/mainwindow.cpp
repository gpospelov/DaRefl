// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QCloseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>
#include <darefl/mainwindow/actionmanager.h>
#include <darefl/mainwindow/importwindow.h>
#include <darefl/mainwindow/mainbarwidget.h>
#include <darefl/mainwindow/mainwindow.h>
#include <darefl/mainwindow/refldockwindow.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/welcomeview/welcomeview2.h>

namespace
{
const QString main_window_group = "MainWindow";
const QString size_key = "size";
const QString pos_key = "pos";
} // namespace

MainWindow::MainWindow()
    : models(std::make_unique<ApplicationModels>()), m_actionManager(new ActionManager(this))
{
    init_application();
    init_components();
    init_connections();
    setCentralWidget(bar_widget);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (welcome_view->canCloseProject()) {
        write_settings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::init_application()
{
    QCoreApplication::setApplicationName("quickrefl");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationName("qt-mvvm");

    QSettings settings;
    if (settings.childGroups().contains(main_window_group)) {
        settings.beginGroup(main_window_group);
        resize(settings.value(size_key, QSize(400, 400)).toSize());
        move(settings.value(pos_key, QPoint(200, 200)).toPoint());
        settings.endGroup();
    }
}

void MainWindow::init_components()
{
    welcome_view = new WelcomeView2(models.get());
    import_window = new ImportWindow(models.get());
    refl_window = new ReflDockWindow(models.get());
    bar_widget = new MainBarWidget;

    bar_widget->addWidget(welcome_view, "Project");
    bar_widget->addWidget(import_window, "Data");
    bar_widget->addWidget(refl_window, "Simulation");
    bar_widget->addWidget(new QWidget, "Fitting");
    bar_widget->addWidget(new QWidget, "Export");
    bar_widget->addWidget(new QWidget, "Settings");
    bar_widget->setCurrentIndex(1);
}

//! Setup main connections.

void MainWindow::init_connections()
{
    // connect ActionManager signals with WelcomeView slots
    connect(m_actionManager, &ActionManager::createNewProjectRequest, welcome_view,
            &WelcomeView2::onCreateNewProject);
    connect(m_actionManager, &ActionManager::openExistingProjectRequest, welcome_view,
            &WelcomeView2::onOpenExistingProject);
    connect(m_actionManager, &ActionManager::saveCurrentProjectRequest, welcome_view,
            &WelcomeView2::onSaveCurrentProject);
    connect(m_actionManager, &ActionManager::saveProjectAsRequest, welcome_view,
            &WelcomeView2::onSaveProjectAs);
}

void MainWindow::write_settings()
{
    QSettings settings;
    settings.beginGroup(main_window_group);
    settings.setValue(size_key, size());
    settings.setValue(pos_key, pos());
    settings.endGroup();
}
