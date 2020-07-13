// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H

#include <QObject>

//! Actions for ImportDataEditor.

class ImportDataEditorActions : public QObject
{
    Q_OBJECT

public:
    ImportDataEditorActions(QObject* parent = nullptr);
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
