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

#include <darefl/mainwindow/editorwidget.h>

class ApplicationModels;
class LayerEditorActions;
class LayerEditorToolBar;
class LayerEditorWidget;

namespace ModelView
{
class AbstractViewModel;
}

//! Layer editor.

class LayerEditor : public EditorWidget
{
    Q_OBJECT
public:
    LayerEditor(QWidget* parent = nullptr);
    ~LayerEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void selectionChanged();

    LayerEditorToolBar* toolbar() const;

private:
    LayerEditorActions* m_actions{nullptr};
    LayerEditorWidget* m_editorWidget{nullptr};
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITOR_H
