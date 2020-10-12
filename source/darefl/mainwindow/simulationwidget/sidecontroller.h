// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_SIMULATIONWIDGET_SIDECONTROLLER_H
#define MAINWINDOW_SIMULATIONWIDGET_SIDECONTROLLER_H

#include <QList>
#include <QObject>
#include <memory>

class QMainWindow;
class SideWidget;
class EditorWidget;

//! Handles appearance of docked widgets in the QMainWindow context.

class SideController : public QObject
{
    Q_OBJECT

public:
    enum LayoutType { left, right };

    SideController(QMainWindow* main_window, LayoutType layout_type = LayoutType::left);
    ~SideController();

    void addWidgetToList(EditorWidget* widget);
    void addWidgetCenter(QWidget* widget);

private:
    void setupLayout(QMainWindow* main_window, Qt::DockWidgetArea area);

private:
    QWidget* p_graph_area{nullptr};
    SideWidget* p_editor_widgets{nullptr};
};

#endif // MAINWINDOW_SIMULATIONWIDGET_SIDECONTROLLER_H
