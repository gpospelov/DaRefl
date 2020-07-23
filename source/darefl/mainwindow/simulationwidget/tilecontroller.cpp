// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDockWidget>
#include <QMainWindow>
#include <darefl/mainwindow/simulationwidget/tilecontroller.h>
#include <map>
#include <stdexcept>

//! Keeps together info about the dock, the area it occupies and widget it holds.

struct DockWidgetInfo {
    QDockWidget* dock{nullptr};
    Qt::DockWidgetArea area{Qt::NoDockWidgetArea};
    QWidget* widget{nullptr};

    DockWidgetInfo() {}
    DockWidgetInfo(QDockWidget* dock, QWidget* widget, Qt::DockWidgetArea area)
        : dock(dock), area(area), widget(widget)
    {
    }
};

//! Implementation of TileController.

struct TileController::TileControllerImpl {
    QMainWindow* main_window{nullptr};
    std::map<int, DockWidgetInfo> docks;

    TileControllerImpl(QMainWindow* main_window) : main_window(main_window) {}

    void addWidget(int index, QWidget* widget, Qt::DockWidgetArea area)
    {
        if (docks.find(index) != docks.end())
            throw std::runtime_error("Error in TileController: attempt to add widget id twice");

        auto dock = new QDockWidget;
        dock->setWidget(widget);
        dock->setWindowTitle(widget->windowTitle());
        dock->setTitleBarWidget(new QWidget);
        widget->setMinimumSize(0, 0);
        widget->setMaximumSize(1e6, 1e6);

        main_window->addDockWidget(area, dock);
        docks[index] = DockWidgetInfo(dock, widget, area);
    }
};

//! TileController c-tor.

TileController::TileController(QMainWindow* main_window)
    : QObject(main_window), p_impl(std::make_unique<TileControllerImpl>(main_window))
{
}

void TileController::addWidget(int index, QWidget* widget, Qt::DockWidgetArea area)
{
    p_impl->addWidget(index, widget, area);
}

TileController::~TileController() = default;
