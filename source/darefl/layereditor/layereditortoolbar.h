// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H
#define DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H

#include <QToolBar>

class LayerEditorActions;

//! Layer editor toolbar.

class LayerEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent = nullptr);
    ~LayerEditorToolBar() = default;

private:
    QMenu* create_layer_menu(LayerEditorActions* editor_actions);
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITORTOOLBAR_H
