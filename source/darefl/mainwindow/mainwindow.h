// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_MAINWINDOW_H
#define DAREFL_MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class WelcomeView;
class ImportWindow;
class ReflDockWindow;
class MainBarWidget;
class ApplicationModels;
class ActionManager;
class SettingsView;

//! Application main window.

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void init_application();
    void init_components();
    void init_connections();
    void write_settings();

    std::unique_ptr<ApplicationModels> models;
    ActionManager* m_actionManager{nullptr};
    WelcomeView* m_welcomeView{nullptr};
    ImportWindow* m_importWindow{nullptr};
    ReflDockWindow* m_reflWindow{nullptr};
    SettingsView* m_settingsView{nullptr};
    MainBarWidget* m_barWidget{nullptr};
};

#endif // DAREFL_MAINWINDOW_MAINWINDOW_H
