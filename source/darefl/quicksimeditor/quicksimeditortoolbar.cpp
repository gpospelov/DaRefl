// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QCheckBox>
#include <QDebug>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <darefl/quicksimeditor/quicksimeditortoolbar.h>

// namespace
//{
// const int initial_value = 50;
// const int min_value = 0;
// const int max_value = 100;
//} // namespace

QuickSimEditorToolBar::QuickSimEditorToolBar(QWidget* parent)
    : EditorToolBar("Simulation", parent), live_checkbox(new QCheckBox),
      progressbar(new QProgressBar)
{
    const int toolbar_icon_size = 24;
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    setup_simulation_elements();
    add_wide_separator();

    setup_plot_elements();
}

//! Set progress bar to given value.

void QuickSimEditorToolBar::onProgressChanged(int value)
{
    progressbar->setValue(value);
}

void QuickSimEditorToolBar::add_wide_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

//! Setups elements to run simulation.

void QuickSimEditorToolBar::setup_simulation_elements()
{
    // live check box and label
    const QString live_tooltip = "Automatically run simulation and update plot\n"
                                 "on any multilayer change.";
    live_checkbox->setCheckState(Qt::Checked);
    live_checkbox->setToolTip(live_tooltip);
    auto on_check_state = [this](int state) { realTimeRequest(state == Qt::Checked); };
    connect(live_checkbox, &QCheckBox::stateChanged, on_check_state);
    addWidget(live_checkbox);
    auto label = new QLabel("Live");
    label->setToolTip(live_tooltip);
    addWidget(label);

    // run simulation
    auto run_action = new QAction("Run", this);
    run_action->setIcon(QIcon(":/icons/play-circle-outline.svg"));
    run_action->setToolTip("Run simulation for current multilayer state");
    connect(run_action, &QAction::triggered, this, &QuickSimEditorToolBar::runSimulationRequest);
    addAction(run_action);

    // progress bar
    progressbar->setFixedWidth(150);
    progressbar->setTextVisible(false);
    addWidget(progressbar);

    // cancel simulation
    auto cancel_action = new QAction("Cancel", this);
    cancel_action->setIcon(QIcon(":/icons/close-circle-outline.svg"));
    cancel_action->setToolTip("Cancel running simulation");
    connect(cancel_action, &QAction::triggered, this, &QuickSimEditorToolBar::cancelPressed);
    addAction(cancel_action);
}

//! Setups actions to reset plot and access its settings.

void QuickSimEditorToolBar::setup_plot_elements()
{
    auto reset_view = new QAction("Replot", this);
    reset_view->setToolTip("Set plot axes to default range");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    connect(reset_view, &QAction::triggered, this, &QuickSimEditorToolBar::resetViewRequest);
    addAction(reset_view);
}
