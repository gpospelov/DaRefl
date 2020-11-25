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

namespace ModelView
{
class UndoStackInterface;
}

class ExperimentalDataModel;
class DataSelectionModel;
class QItemSelection;

//! Actions for ImportDataEditor.

class ImportDataEditorActions : public QObject
{
    Q_OBJECT

public:
    ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent = nullptr);

    void setSelectionModel(DataSelectionModel* selection_model);

    bool isUndoEnabled() const;

public slots:
    void onAddCanvas();
    void onMergeCanvases();
    void onDeleteItem();
    void onUndo();
    void onRedo();

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    ModelView::UndoStackInterface* undoStack() const;

    ExperimentalDataModel* m_dataModel{nullptr};
    DataSelectionModel* m_selectionModel{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITORACTIONS_H
