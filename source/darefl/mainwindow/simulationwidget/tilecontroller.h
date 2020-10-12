// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_SIMULATIONWIDGET_TILECONTROLLER_H
#define MAINWINDOW_SIMULATIONWIDGET_TILECONTROLLER_H

#include <QObject>
#include <memory>

class QMainWindow;

//! Handles appearance of docked widgets in the QMainWindow context.

class TileController : public QObject
{
    Q_OBJECT

public:
    TileController(QMainWindow* main_window);
    ~TileController();

    void addWidget(int index, QWidget* widget, Qt::DockWidgetArea area);

private:
    struct TileControllerImpl;
    std::unique_ptr<TileControllerImpl> p_impl;
};

#endif // MAINWINDOW_SIMULATIONWIDGET_TILECONTROLLER_H
