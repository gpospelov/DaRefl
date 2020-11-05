// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLayout>
#include <QMainWindow>

#include <darefl/layereditor/layereditor.h>
#include <darefl/materialeditor/materialeditor.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/sldeditor/sldeditor.h>
#include <darefl/model/applicationmodels.h>

#include <darefl/mainwindow/simulationwidget/sidecontroller.h>
#include <darefl/mainwindow/simulationwidget/simwidgetcontroller.h>
#include <darefl/mainwindow/simulationwidget/tilecontroller.h>

//! The constructor
SimWidgetController::SimWidgetController(QWidget* parent, QMainWindow* target)
    : QObject(parent), p_target_window(target), p_mat_editor(new MaterialEditor),
      p_layer_editor(new LayerEditor), p_sld_editor(new SLDEditor),
      p_q_sim_editor(new QuickSimEditor)
{
    setTiledLayout();
}

//! The destructor
SimWidgetController::~SimWidgetController() = default;

//! Set up the models
void SimWidgetController::setModels(ApplicationModels* models)
{
    p_mat_editor->setModels(models);
    p_layer_editor->setModels(models);
    p_sld_editor->setModels(models);
    p_q_sim_editor->setModels(models);
}

//! sets the default tiled layout mode
void SimWidgetController::setTiledLayout()
{
    cleanLayout();

    auto temp_layout_controller = new TileController(p_target_window);
    temp_layout_controller->addWidget(0, p_mat_editor, Qt::TopDockWidgetArea);
    temp_layout_controller->addWidget(1, p_layer_editor, Qt::TopDockWidgetArea);
    temp_layout_controller->addWidget(3, p_sld_editor, Qt::BottomDockWidgetArea);
    temp_layout_controller->addWidget(4, p_q_sim_editor, Qt::BottomDockWidgetArea);
    p_layout_controller = temp_layout_controller;

    m_current_layout = LayoutType::tiled;
}

//! sets the left layout mode
void SimWidgetController::setSideLeftLayout()
{
    cleanLayout();

    auto temp_layout_controller =
        new SideController(p_target_window, SideController::LayoutType::left);
    temp_layout_controller->addWidgetCenter(p_q_sim_editor);
//    temp_layout_controller->addWidgetToList(p_mat_editor);
//    temp_layout_controller->addWidgetToList(p_layer_editor);
//    temp_layout_controller->addWidgetToList(p_sld_editor);
    p_layout_controller = temp_layout_controller;

    m_current_layout = LayoutType::left;
}

//! set the right layout mode
void SimWidgetController::setSideRightLayout()
{
    cleanLayout();

    auto temp_layout_controller =
        new SideController(p_target_window, SideController::LayoutType::right);
    temp_layout_controller->addWidgetCenter(p_q_sim_editor);
//    temp_layout_controller->addWidgetToList(p_mat_editor);
//    temp_layout_controller->addWidgetToList(p_layer_editor);
//    temp_layout_controller->addWidgetToList(p_sld_editor);
    p_layout_controller = temp_layout_controller;

    m_current_layout = LayoutType::right;
}

//! Cleans up all widgets and removes them from the layout
void SimWidgetController::cleanLayout()
{
    p_mat_editor->setParent(nullptr);
    p_layer_editor->setParent(nullptr);
    p_sld_editor->setParent(nullptr);
    p_q_sim_editor->setParent(nullptr);

    delete p_layout_controller;
    p_layout_controller = nullptr;

    if (p_target_window->layout() != nullptr) {
        QLayoutItem* item;
        while ((item = p_target_window->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }
}
