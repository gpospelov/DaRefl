// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_SIMULATIONWIDGET_H
#define DAREFL_MAINWINDOW_SIMULATIONWIDGET_H

#include <QWidget>
#include <memory>

class SimWidgetController;
class QMainWindow;
class QToolBar;
class ApplicationModels;

class SimulationWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationWidget(QWidget* parent = nullptr);
    ~SimulationWidget();

    void setModels(ApplicationModels* models);

private:
    void setupToolbar();

private:
    QToolBar* p_toolbar;
    QMainWindow* p_main_area;
    std::unique_ptr<SimWidgetController> p_widget_ctrl;
};

#endif // DAREFL_MAINWINDOW_SIMULATIONWIDGET_H
