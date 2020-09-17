// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_SIMULATIONVIEWV2_H
#define DAREFL_MAINWINDOW_SIMULATIONVIEWV2_H

#include <QMainWindow>
#include <memory>

class ApplicationModels;
class CollapsibleListWidget;
class QuickSimEditor;

//! Main simulation window with all components for quick sample editing and simulations.

class SimulationViewV2 : public QMainWindow
{
    Q_OBJECT
public:
    SimulationViewV2(ApplicationModels* m_models, QWidget* parent = nullptr);

private:
    CollapsibleListWidget* m_editorList{nullptr};
    QuickSimEditor* m_simEditor{nullptr};
    ApplicationModels* m_models{nullptr};
};

#endif // DAREFL_MAINWINDOW_SIMULATIONVIEWV2_H
