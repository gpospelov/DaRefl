// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLabel>
#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <darefl/mainwindow/simulationwidget/simulationwidget.h>
#include <darefl/mainwindow/simulationwidget/simwidgetcontroller.h>
#include <darefl/model/applicationmodels.h>

//! The constructor
SimulationWidget::SimulationWidget(QWidget* parent)
    : QWidget(parent), p_toolbar(new QToolBar), p_main_area(new QMainWindow),
      p_widget_ctrl(std::make_unique<SimWidgetController>(this, p_main_area))
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(p_toolbar);
    layout->addWidget(p_main_area);
    setupToolbar();
}

//! The destructor
SimulationWidget::~SimulationWidget() = default;

void SimulationWidget::setupToolbar()
{
    const int toolbar_icon_size = 24;
    p_toolbar->setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    p_toolbar->addWidget(empty);
    p_toolbar->addSeparator();

    QToolButton* select_tiles;

    select_tiles = new QToolButton;
    select_tiles->setToolTip("Set axes to default range.");
    select_tiles->setIcon(QIcon(":/icons/view-grid.svg"));
    p_toolbar->addWidget(select_tiles);
    connect(select_tiles, &QToolButton::clicked, [this]() { p_widget_ctrl->setTiledLayout(); });

    select_tiles = new QToolButton;
    select_tiles->setToolTip("Set axes to default range.");
    select_tiles->setIcon(QIcon(":/icons/dock-left.svg"));
    p_toolbar->addWidget(select_tiles);
    connect(select_tiles, &QToolButton::clicked, [this]() { p_widget_ctrl->setSideLeftLayout(); });

    select_tiles = new QToolButton;
    select_tiles->setToolTip("Set axes to default range.");
    select_tiles->setIcon(QIcon(":/icons/dock-right.svg"));
    p_toolbar->addWidget(select_tiles);
    connect(select_tiles, &QToolButton::clicked, [this]() { p_widget_ctrl->setSideRightLayout(); });
}

//! Set up the models
void SimulationWidget::setModels(ApplicationModels* models)
{
    p_widget_ctrl->setModels(models);
}
