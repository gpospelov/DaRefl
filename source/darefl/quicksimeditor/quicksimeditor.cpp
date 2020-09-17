// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTabWidget>
#include <QVBoxLayout>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/jobmodel.h>
#include <darefl/quicksimeditor/quicksimcontroller.h>
#include <darefl/quicksimeditor/quicksimeditor.h>
#include <darefl/quicksimeditor/quicksimeditortoolbar.h>
#include <darefl/quicksimeditor/simplotcontroller.h>
#include <darefl/quicksimeditor/simplotwidget.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

QuickSimEditor::QuickSimEditor(QWidget* parent)
    : EditorWidget(parent), sim_controller(new QuickSimController(this)),
      plot_controller(new SimPlotController(this)), m_plotWidget(new SimPlotWidget)
{
    setWindowTitle(QString("Reflectivity plot"));
    p_toolbar = dynamic_cast<EditorToolBar*>(new QuickSimEditorToolBar);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(p_toolbar);
    layout->addWidget(m_plotWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setup_toolbar_connections();
    setup_controller_connections();
}

QuickSimEditor::~QuickSimEditor() = default;

//! Set the mododel for the different items
void QuickSimEditor::setModels(ApplicationModels* models)
{
    app_models = models;
    sim_controller->setModels(models);
    plot_controller->setModels(models);
    // toolbar->setModels(models);
    m_plotWidget->setModels(models);
}

QSize QuickSimEditor::sizeHint() const
{
    return StyleUtils::DockSizeHint();
}

QSize QuickSimEditor::minimumSizeHint() const
{
    return StyleUtils::DockMinimumSizeHint();
}

//! Connects signals from toolbar.

void QuickSimEditor::setup_toolbar_connections()
{
    // Request to reset plot is propagated from toolbar to viewports.
    auto on_reset_view = [this]() { m_plotWidget->update_viewport(); };
    connect(dynamic_cast<QuickSimEditorToolBar*>(p_toolbar),
            &QuickSimEditorToolBar::resetViewRequest, on_reset_view);

    // Simulation interrupt request is propagated from toolbar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(p_toolbar), &QuickSimEditorToolBar::cancelPressed,
            sim_controller, &QuickSimController::onInterruptRequest);

    // Request for real time mode is propagated from toobar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(p_toolbar),
            &QuickSimEditorToolBar::realTimeRequest, sim_controller,
            &QuickSimController::onRealTimeRequest);

    // RUn simulation is propagated from toobar to controller.
    connect(dynamic_cast<QuickSimEditorToolBar*>(p_toolbar),
            &QuickSimEditorToolBar::runSimulationRequest, sim_controller,
            &QuickSimController::onRunSimulationRequest);
}

//! Connects signals from controller.

void QuickSimEditor::setup_controller_connections()
{
    // Progress values propagated from controller to toolbar.
    connect(sim_controller, &QuickSimController::progressChanged,
            dynamic_cast<QuickSimEditorToolBar*>(p_toolbar),
            &QuickSimEditorToolBar::onProgressChanged);
}
