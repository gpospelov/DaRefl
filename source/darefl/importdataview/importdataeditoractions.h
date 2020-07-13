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

class RealDataModel;
class DataSelectionModel;

//! Actions for ImportDataEditor.

class ImportDataEditorActions : public QObject
{
    Q_OBJECT

public:
    ImportDataEditorActions(RealDataModel* model, DataSelectionModel* selectionModel,
                            QObject* parent = nullptr);

public slots:
    void addDataGroup();
    void mergeDataGroups();
    void deleteItem();
    void resetAll();

private:
    RealDataModel* m_dataModel{nullptr};
    DataSelectionModel* m_selectionModel{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
