// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAR_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAR_H

#include <QToolBar>

class ImportDataEditorActions;

//! Toolbar for ImportDataEditor.

class ImportDataEditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    ImportDataEditorToolBar(ImportDataEditorActions* editorActions, QWidget* parent = nullptr);

signals:
    void invokeImportDialog();
    void update_viewport();

private slots:
    void resetAll();

private:
    ImportDataEditorActions* m_editorActions{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAR_H
