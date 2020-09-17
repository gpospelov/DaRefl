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
#include <darefl/mainwindow/simulationview_v1.h>
#include <darefl/materialeditor/materialeditor.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/quicksimeditor/instrumentpropertyeditor.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/sldeditor/sldeditor.h>

SimulationViewV1::SimulationViewV1(ApplicationModels* models, QWidget* parent)
    : QMainWindow(parent), m_toolBar(new QToolBar), m_docksController(new DocksController(this)),
      m_models(models), m_quickSimEditor(new QuickSimEditor(this))
{
    setup_toolbar();

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    auto material_editor = new MaterialEditor(this);
    auto layer_editor = new LayerEditor(this);
    auto sld_editor = new SLDEditor(this);
    auto instrument_editor = new InstrumentPropertyEditor(this);

    m_docksController->addWidget(0, material_editor, Qt::LeftDockWidgetArea);
    m_docksController->addWidget(1, layer_editor, Qt::LeftDockWidgetArea);
    m_docksController->addWidget(3, sld_editor, Qt::LeftDockWidgetArea);
    m_docksController->addWidget(4, instrument_editor, Qt::BottomDockWidgetArea);

    setCentralWidget(m_quickSimEditor);

    material_editor->setModels(models);
    layer_editor->setModels(models);
    sld_editor->setModels(models);
    m_quickSimEditor->setModels(models);
    instrument_editor->setModels(models);
}

SimulationViewV1::~SimulationViewV1() = default;

void SimulationViewV1::setup_toolbar()
{
    const int toolbar_icon_size = 24;
    m_toolBar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    addToolBar(m_toolBar);
}
