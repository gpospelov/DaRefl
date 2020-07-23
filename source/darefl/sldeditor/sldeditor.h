// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDEDITOR_H
#define DAREFL_SLDEDITOR_SLDEDITOR_H

class SLDEditorActions;
class SLDEditorToolBar;
class SLDViewWidget;
class ApplicationModels;

#include <darefl/mainwindow/editorwidget.h>

//! The SLD editor QWidget
class SLDEditor : public EditorWidget
{

public:
    SLDEditor(QWidget* parent = nullptr);
    ~SLDEditor();

    void setModels(ApplicationModels* models);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    SLDEditorActions* p_editor_actions{nullptr};
    SLDViewWidget* p_view_widget{nullptr};
};

#endif // DAREFL_SLDEDITOR_SLDEDITOR_H
