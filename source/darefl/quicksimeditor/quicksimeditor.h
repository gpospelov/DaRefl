// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H

#include <darefl/mainwindow/editorwidget.h>

class JobModel;
class ApplicationModels;
class QuickSimController;
class QuickSimEditorToolBar;
class SimPlotController;
class SimPlotWidget;

//! Quick reflectivity simulations.

class QuickSimEditor : public EditorWidget
{
    Q_OBJECT
public:
    QuickSimEditor(QWidget* parent = nullptr);
    ~QuickSimEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    void setup_toolbar_connections();
    void setup_controller_connections();

    ApplicationModels* app_models{nullptr};
    QuickSimController* sim_controller{nullptr};
    SimPlotController* plot_controller{nullptr};
    SimPlotWidget* m_plotWidget{nullptr};
};

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMEDITOR_H
