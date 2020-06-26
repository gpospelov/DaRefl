// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_REFLDOCKWINDOW_H
#define DAREFL_MAINWINDOW_REFLDOCKWINDOW_H

#include <QMainWindow>
#include <memory>

class DocksController;
class ApplicationModels;
class QToolBar;

//! Main reflectometry window with all components for quick sample editing and simulations.

class ReflDockWindow : public QMainWindow
{
    Q_OBJECT
public:
    ReflDockWindow(ApplicationModels* models, QWidget* parent = nullptr);
    ~ReflDockWindow();

private:
    void setup_toolbar();
    void setup_centralwidget();

    QToolBar* toolbar{nullptr};
    DocksController* docks_controller{nullptr};
    ApplicationModels* models;
};

#endif  // DAREFL_MAINWINDOW_REFLDOCKWINDOW_H
