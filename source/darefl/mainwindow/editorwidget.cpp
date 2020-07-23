// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/mainwindow/editorwidget.h>

EditorWidget::EditorWidget(QWidget* parent) : QWidget(parent) {}

EditorWidget::~EditorWidget() = default;

//! The toolbar pointer
EditorToolBar* EditorWidget::toolbar() const
{
    return p_toolbar;
}

//! Minimum heigh tof the widget for the resizing
int EditorWidget::getMiniumuHeight() const
{
    if (!p_toolbar)
        return 40;

    if (p_toolbar->toggleState()){
        return p_toolbar->sizeHint().height();
    }else{
        return p_toolbar->sizeHint().height()+40;
    }
}

//! resizeable state depending on the toolbar
bool EditorWidget::resizeable() const
{
    if (!p_toolbar)
        return true;

    if (p_toolbar->toggleState()){
        return false;
    }else{
        return true;
    }
}