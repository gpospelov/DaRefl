// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYEREDITORACTIONS_H
#define DAREFL_LAYEREDITOR_LAYEREDITORACTIONS_H

#include <QObject>
#include <memory>

class SampleModel;
class LayerSelectionModel;

//! Handles user actions applied to layer tree.
//! Belongs to LayerEditor.

class LayerEditorActions : public QObject
{
    Q_OBJECT
public:
    LayerEditorActions(SampleModel* model, QObject* parent = nullptr);
    ~LayerEditorActions();

    void onAddLayer();
    void onAddMultiLayer();
    void onClone();
    void onRemove();
    void onMoveUp();
    void onMoveDown();

    void setSelectionModel(LayerSelectionModel* selection_model);

private:
    struct LayerEditorActionsImpl;
    std::unique_ptr<LayerEditorActionsImpl> p_impl;
};

#endif // DAREFL_LAYEREDITOR_LAYEREDITORACTIONS_H
