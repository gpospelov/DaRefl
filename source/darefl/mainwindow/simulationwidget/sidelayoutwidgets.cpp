// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/mainwindow/editorwidget.h>
#include <darefl/mainwindow/simulationwidget/sidelayoutwidgets.h>

#include <QMouseEvent>
#include <QScrollBar>
#include <QVBoxLayout>
#include <iostream>

//! The c-tor for the dock widget
SideDockHandle::SideDockHandle(QWidget* parent)
    : QWidget(parent), m_button_pressed(false), m_last_pos(QPoint(0, 0))
{
    setFixedHeight(5);
    setStyleSheet("background-color: red;");
    show();
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMouseTracking(true);
}

//! The d-tor for the dock widget
SideDockHandle::~SideDockHandle() = default;

//! The enter event of the mouse
void SideDockHandle::enterEvent(QEvent* event)
{
    setCursor(Qt::SizeVerCursor);
    m_button_pressed = false;
}

//! The exit event of the mouse
void SideDockHandle::leaveEvent(QEvent* event)
{
    unsetCursor();
    m_button_pressed = false;
}

//! The mouse press event event of the mouse
void SideDockHandle::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_last_pos = mapToGlobal(event->pos());
        m_button_pressed = true;
    }
}

//! The mouse press event event of the mouse
void SideDockHandle::mouseReleaseEvent(QMouseEvent* event)
{
    m_button_pressed = false;
}

//! The mouse move event event of the mouse
void SideDockHandle::mouseMoveEvent(QMouseEvent* event)
{
    if (m_button_pressed) {
        emit onMouseDrag((mapToGlobal(event->pos()).y() - m_last_pos.y()));
        m_last_pos = mapToGlobal(event->pos());
    } else {
        QWidget::mouseMoveEvent(event);
    }
}

// ---------------------------------------------------------------------------//

//! The c-tor for the dock widget
SideDockWidget::SideDockWidget(std::string name, EditorWidget* widget, QWidget* parent)
    : QWidget(parent), p_side_handle(new SideDockHandle(this)), p_center_widget(widget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(p_center_widget);
    layout->addWidget(p_side_handle);
    p_center_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setUpHandle();

    connect(dynamic_cast<EditorWidget*>(p_center_widget), &EditorWidget::resized, this,
            &SideDockWidget::handleResizeRequestForced);

    handleResizeRequest(0);
}

//! The d-tor for the dock widget
SideDockWidget::~SideDockWidget() = default;

//! Connect the handle widget
void SideDockWidget::setUpHandle()
{
    connect(p_side_handle, &SideDockHandle::onMouseDrag, this,
            &SideDockWidget::handleResizeRequest);
}

//! Create the handle item
void SideDockWidget::handleResizeRequest(int delta_height)
{
    if (!p_center_widget->resizeable())
        return;

    if (p_center_widget->size().height() + delta_height < p_center_widget->getMiniumuHeight())
        return;
        
    emit requestParentResize(delta_height);
    p_side_handle->blockSignals(true);
    p_center_widget->setFixedHeight(p_center_widget->size().height() + delta_height);
    p_side_handle->blockSignals(false);
}

//! Force the resize request
void SideDockWidget::handleResizeRequestForced(int delta_height)
{
    emit requestParentResize(delta_height);
    p_side_handle->blockSignals(true);
    p_center_widget->setFixedHeight(p_center_widget->size().height() + delta_height);
    p_side_handle->blockSignals(false);
}

// ---------------------------------------------------------------------------//

//! The c-tor for the window
SideWidget::SideWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setFixedHeight(0);
}

//! The d-tor for the window
SideWidget::~SideWidget() = default;

void SideWidget::addWidget(std::string name, EditorWidget* child)
{
    auto widget = new SideDockWidget(name, child, this);
    layout()->addWidget(widget);
    setFixedHeight(size().height() + widget->sizeHint().height());
    connect(widget, &SideDockWidget::requestParentResize,
            [this](int delta_height) { emit onResizeEvent(delta_height); });
}

//! Resize the main height requested by child
void SideWidget::resizeHeight(int delta_height)
{
    setFixedHeight(size().height() + delta_height);
}

// ---------------------------------------------------------------------------//

//! The c-tor for the window
SideScrollArea::SideScrollArea(QWidget* parent) : QScrollArea(parent)
{
    setWidgetResizable(true);
}

//! The d-tor for the window
SideScrollArea::~SideScrollArea() = default;

//! Resize the main height requested by child
void SideScrollArea::setWidget(SideWidget* widget)
{
    QScrollArea::setWidget(widget);
    connect(widget, &SideWidget::onResizeEvent, this, &SideScrollArea::handleChildResize);
}

//! Handle the resize request of the child and handle bottom scroll
void SideScrollArea::handleChildResize(int delta_height)
{
    QScrollBar* scrollbar = verticalScrollBar();
    bool scrollbarAtBottom = (scrollbar->value() >= (scrollbar->maximum() - 20));

    dynamic_cast<SideWidget*>(widget())->resizeHeight(delta_height);

    if (scrollbarAtBottom)
        scrollbar->setValue(scrollbar->maximum());
}
