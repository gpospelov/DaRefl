// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_SIMULATIONWIDGET_SIDELAYOUTWIDGETS_H
#define MAINWINDOW_SIMULATIONWIDGET_SIDELAYOUTWIDGETS_H

#include <QPoint>
#include <QScrollArea>
#include <QWidget>

class QWidget;
class EditorWidget;
class QResizeEvent;

//! The custome dock widget
class SideDockHandle : public QWidget
{
    Q_OBJECT
public:
    SideDockHandle(QWidget* parent = nullptr);
    ~SideDockHandle();

signals:
    void onMouseDrag(int delta_height);

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool m_button_pressed;
    QPoint m_last_pos;
};

// ---------------------------------------------------------------------------//

//! The custome dock widget
class SideDockWidget : public QWidget
{
    Q_OBJECT
public:
    SideDockWidget(std::string name, EditorWidget* widget, QWidget* parent = nullptr);
    ~SideDockWidget();

signals:
    void requestParentResize(int delta_height);

private:
    void setUpHandle();
    void handleResizeRequest(int delta_height);
    void handleResizeRequestForced(int delta_height);
    void handleResizeEvent(QResizeEvent* event);

private:
    SideDockHandle* p_side_handle{nullptr};
    EditorWidget* p_center_widget{nullptr};
};

// ---------------------------------------------------------------------------//

//! The custom window widget
class SideWidget : public QWidget
{
    Q_OBJECT
public:
    SideWidget(QWidget* parent = nullptr);
    ~SideWidget();

    void addWidget(std::string name, EditorWidget* child);
    void resizeHeight(int delta_height);

signals:
    void onResizeEvent(int delta_height);
};

// ---------------------------------------------------------------------------//

//! The custom window widget
class SideScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    SideScrollArea(QWidget* parent = nullptr);
    ~SideScrollArea();

    void setWidget(SideWidget* widget);

private:
    void setWidget(QWidget* widget);
    void handleChildResize(int delta_height);
};

#endif // MAINWINDOW_SIMULATIONWIDGET_SIDELAYOUTWIDGETS_H
