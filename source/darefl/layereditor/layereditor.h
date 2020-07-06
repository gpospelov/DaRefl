// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITOR_H
#define DAREFL_LAYEREDITOR_LAYEREDITOR_H

#include <QWidget>

class ApplicationModels;
class LayerEditorActions;
class LayerEditorToolBar;
class LayerEditorWidget;

namespace ModelView
{
class AbstractViewModel;
}

//! Layer editor.

class LayerEditor : public QWidget
{
    Q_OBJECT
public:
    LayerEditor(ApplicationModels* models, QWidget* parent = nullptr);
    ~LayerEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void selectionChanged();

private:
    LayerEditorActions* actions{nullptr};
    LayerEditorToolBar* toolbar{nullptr};
    LayerEditorWidget* editor_widget{nullptr};
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITOR_H
