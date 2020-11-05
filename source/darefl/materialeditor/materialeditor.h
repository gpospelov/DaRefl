// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MATERIALEDITOR_MATERIALEDITOR_H
#define DAREFL_MATERIALEDITOR_MATERIALEDITOR_H

#include <darefl/mainwindow/editorwidget.h>

class ApplicationModels;
class MaterialEditorActions;
class MaterialEditorToolBar;
class MaterialEditorWidget;

//! Material editor.

class MaterialEditor : public EditorWidget
{
    Q_OBJECT
public:
    MaterialEditor(QWidget* parent = nullptr);
    ~MaterialEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    MaterialEditorActions* m_actions{nullptr};
    MaterialEditorWidget* m_editorWidget{nullptr};
};

#endif // DAREFL_MATERIALEDITOR_MATERIALEDITOR_H
