// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALEDITORACTIONS_H
#define DAREFL_MATERIALEDITOR_MATERIALEDITORACTIONS_H

#include <QObject>
#include <memory>

class MaterialModel;
class MaterialSelectionModel;

//! Handles user actions applied to material table.
//! Belongs to MaterialEditor.

class MaterialEditorActions : public QObject
{
    Q_OBJECT

public:
    MaterialEditorActions(QObject* parent = nullptr);
    ~MaterialEditorActions();

    void setModel(MaterialModel* model);

    void onAddMaterial();
    void onCloneMaterial();
    void onRemoveMaterial();
    void onMoveUp();
    void onMoveDown();
    void onExport();
    void onImport();

    void setMaterialSelectionModel(MaterialSelectionModel* selection_model);

private:
    struct MaterialEditorActionsImpl;
    std::unique_ptr<MaterialEditorActionsImpl> p_impl;
};

#endif // DAREFL_MATERIALEDITOR_MATERIALEDITORACTIONS_H
