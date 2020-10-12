// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_EDITORWIDGET_H
#define DAREFL_MAINWINDOW_EDITORWIDGET_H

#include <QWidget>
#include <darefl/mainwindow/editortoolbar.h>

//! Handles appearance of docked widgets in the QMainWindow context.

class EditorWidget : public QWidget
{
    Q_OBJECT

public:
    EditorWidget(QWidget* parent = nullptr);
    ~EditorWidget();
    EditorToolBar* toolbar() const;
    int getMiniumuHeight() const;
    bool resizeable() const;

signals:
    void resized(int delta_size);
    
protected:
    EditorToolBar* p_toolbar{nullptr};

};

#endif // DAREFL_MAINWINDOW_EDITORWIDGET_H
