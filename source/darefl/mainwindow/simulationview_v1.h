// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_SIMULATIONVIEW_V1_H
#define DAREFL_MAINWINDOW_SIMULATIONVIEW_V1_H

#include <QMainWindow>

class DocksController;
class ApplicationModels;
class QToolBar;
class QuickSimEditor;

//! Main simulation window with all components for quick sample editing and simulations.

class SimulationViewV1 : public QMainWindow
{
    Q_OBJECT
public:
    SimulationViewV1(ApplicationModels* models, QWidget* parent = nullptr);
    ~SimulationViewV1();

private:
    void setup_toolbar();

    QToolBar* m_toolBar{nullptr};
    DocksController* m_docksController{nullptr};
    ApplicationModels* m_models{nullptr};
    QuickSimEditor* m_quickSimEditor{nullptr};
};

#endif // DAREFL_MAINWINDOW_SIMULATIONVIEW_V1_H
