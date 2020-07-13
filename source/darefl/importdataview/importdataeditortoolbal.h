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

//! Toolbar for ImportDataEditor.

class ImportDataEditorToolBar : public QToolBar
{
    Q_OBJECT

public:
    ImportDataEditorToolBar(QWidget* parent = nullptr);
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORTOOLBAR_H
