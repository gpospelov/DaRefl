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
    void init_views();
    void write_settings();

    std::unique_ptr<ApplicationModels> models;
    WelcomeView* welcome_view{nullptr};
    ImportWindow* import_window{nullptr};
    ReflDockWindow* refl_window{nullptr};
    MainBarWidget* bar_widget{nullptr};
};

#endif  // DAREFL_MAINWINDOW_MAINWINDOW_H
