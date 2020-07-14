// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLabel>
#include <QToolBar>
#include <darefl/layereditor/layereditor.h>
#include <darefl/mainwindow/dockscontroller.h>
#include <darefl/mainwindow/refldockwindow.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/sldeditor/sldeditor.h>
#include <darefl/materialeditor/materialeditor.h>

ReflDockWindow::ReflDockWindow(ApplicationModels* models, QWidget* parent)
    : QMainWindow(parent), toolbar(new QToolBar), docks_controller(new DocksController(this)),
      models(models)
{
    setup_toolbar();
    setup_centralwidget();

    auto material_editor = new MaterialEditor(this);
    auto layer_editor = new LayerEditor(this);
    auto sld_editor = new SLDEditor(this);
    auto q_sim_editor = new QuickSimEditor(this);

    docks_controller->addWidget(0, material_editor, Qt::TopDockWidgetArea);
    docks_controller->addWidget(1, layer_editor, Qt::TopDockWidgetArea);
    docks_controller->addWidget(3, sld_editor, Qt::BottomDockWidgetArea);
    docks_controller->addWidget(4, q_sim_editor, Qt::BottomDockWidgetArea);

    material_editor->setModels(models);
    layer_editor->setModels(models);
    sld_editor->setModels(models);
    q_sim_editor->setModels(models);
}

ReflDockWindow::~ReflDockWindow() = default;

void ReflDockWindow::setup_toolbar()
{
    const int toolbar_icon_size = 24;
    toolbar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    addToolBar(toolbar);
    //    setCentralWidget(toolbar);
}

//! Central widget as horizontal thin line.

void ReflDockWindow::setup_centralwidget()
{
    auto central_widget = new QWidget;
    central_widget->setStyleSheet("background-color:red;");
    central_widget->setMinimumHeight(2);
    central_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setCentralWidget(central_widget);
}
