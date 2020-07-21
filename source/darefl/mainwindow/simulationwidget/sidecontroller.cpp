// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDockWidget>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include <darefl/mainwindow/editorwidget.h>
#include <darefl/mainwindow/simulationwidget/sidecontroller.h>
#include <darefl/mainwindow/simulationwidget/sidelayoutwidgets.h>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>

//! SideController c-tor.
SideController::SideController(QMainWindow* main_window, LayoutType layout_type)
    : QObject(main_window), p_graph_area(new QWidget(main_window)),
      p_editor_widgets(new SideWidget(main_window))
{
    p_graph_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto layout = new QVBoxLayout(p_graph_area);
    setupLayout(main_window, (LayoutType::left == layout_type) ? (Qt::LeftDockWidgetArea)
                                                               : (Qt::RightDockWidgetArea));
}

//! Add the widget to the list view
void SideController::addWidgetToList(EditorWidget* widget)
{
    p_editor_widgets->addWidget("lol", widget);
    EditorToolBarMode options;
    options = EditorToolBarMode::Toggle | EditorToolBarMode::Window | EditorToolBarMode::Title;
    widget->toolbar()->setMode(options);
}

//! Add the widget to the center
void SideController::addWidgetCenter(QWidget* widget)
{
    p_graph_area->layout()->addWidget(widget);
}

//! Set up the layout with the list on the left
void SideController::setupLayout(QMainWindow* main_window, Qt::DockWidgetArea area)
{
    main_window->setCentralWidget(p_graph_area);

    auto scroll_area = new SideScrollArea(main_window);
    scroll_area->setWidget(p_editor_widgets);

    auto dock = new QDockWidget;
    dock->setWidget(scroll_area);
    dock->setAllowedAreas(area);
    dock->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    dock->setTitleBarWidget(new QWidget);
    main_window->addDockWidget(area, dock);
}

SideController::~SideController() = default;
