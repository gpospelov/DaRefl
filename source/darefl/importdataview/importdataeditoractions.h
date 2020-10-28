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

class ExperimentalDataModel;
class DataSelectionModel;

//! Actions for ImportDataEditor.

class ImportDataEditorActions : public QObject
{
    Q_OBJECT

public:
    ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent = nullptr);

    void setSelectionModel(DataSelectionModel* selection_model);

public slots:
    void onAddCanvas();
    void onMergeDataGroups();
    void onDeleteItem();
    void onUndo();
    void onRedo();

private:
    ExperimentalDataModel* m_dataModel{nullptr};
    DataSelectionModel* m_selectionModel{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
