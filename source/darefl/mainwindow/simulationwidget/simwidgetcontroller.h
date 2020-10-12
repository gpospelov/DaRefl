// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_SIMULATIONWIDGET_SIMWIDGETCONTROLLER_H
#define MAINWINDOW_SIMULATIONWIDGET_SIMWIDGETCONTROLLER_H

#include <QObject>
#include <vector>

class MaterialEditor;
class LayerEditor;
class SLDEditor;
class QuickSimEditor;
class QWidget;
class QMainWindow;
class QMainWindow;
class ApplicationModels;

//! The controller of all widgets in the simulation window
class SimWidgetController : public QObject
{
    Q_OBJECT

public:
    SimWidgetController(QWidget* parent, QMainWindow* target);
    ~SimWidgetController();

    enum LayoutType { tiled, left, right };
    void setTiledLayout();
    void setSideLeftLayout();
    void setSideRightLayout();
    void cleanLayout();

    void setModels(ApplicationModels* models);

private:
    LayoutType m_current_layout;

    MaterialEditor* p_mat_editor{nullptr};
    LayerEditor* p_layer_editor{nullptr};
    SLDEditor* p_sld_editor{nullptr};
    QuickSimEditor* p_q_sim_editor{nullptr};

    QMainWindow* p_target_window{nullptr};
    QWidget* p_layout_widget{nullptr};
    QObject* p_layout_controller{nullptr};

    std::vector<QMainWindow*> m_windows;
};

#endif // MAINWINDOW_SIMULATIONWIDGET_SIMWIDGETCONTROLLER_H
