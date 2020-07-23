// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_GRAPHEDITOR_GRAPHEDITORTOOLBAR_H
#define DAREFL_GRAPHEDITOR_GRAPHEDITORTOOLBAR_H

#include <darefl/mainwindow/editortoolbar.h>

//! Narrow vertical toolbar for GraphEditor.

class GraphEditorToolBar : public EditorToolBar
{
    Q_OBJECT
public:
    explicit GraphEditorToolBar(QWidget* parent = nullptr);

signals:
    void resetViewport();
};

#endif // DAREFL_GRAPHEDITOR_GRAPHEDITORTOOLBAR_H
