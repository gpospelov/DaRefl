// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
#define DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H

#include <QWidget>
#include <string>

class ExperimentalDataModel;
struct RealDataStruct;
class DataViewModel;
class DataSelectionModel;
class ImportDataEditorActions;
class ImportDataEditorToolBar;
class DataSelectorWidget;
class GraphCanvasWidget;
class CanvasItem;

//! Main editor to import user data.

class ImportDataEditor : public QWidget
{
    Q_OBJECT
public:
    ImportDataEditor(ExperimentalDataModel* model, QWidget* parent = nullptr);

private:
    void setupConnections();
    void setupLayout();

    void selectionChanged();
    void setMergeEnabled(bool enabled);

    void invokeImportDialog();

    std::pair<std::vector<std::string>, int> canvasInfo() const;

    void onImportDialogAccept(const std::vector<RealDataStruct>& experimental_data,
                              CanvasItem* canvas);

private:
    DataSelectionModel* selectionModel() const;

    ExperimentalDataModel* m_dataModel{nullptr};
    DataViewModel* m_viewModel{nullptr};
    ImportDataEditorActions* m_editorActions{nullptr};
    ImportDataEditorToolBar* m_editorToolBar{nullptr};
    DataSelectorWidget* m_dataSelectorWidget{nullptr};
    GraphCanvasWidget* m_graphCanvasWidget{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_IMPORTDATAEDITOR_H
