// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAWIDGETS_IMPORTDATAEDITOR_H
#define DAREFL_IMPORTDATAWIDGETS_IMPORTDATAEDITOR_H

#include <QWidget>
#include <string>

namespace DataImportLogic
{
class ImportOutput;
class ParsedFileOutptut;
} // namespace DataImportLogic

class ExperimentalDataModel;
class RealDataStruct;
class DataViewModel;
class DataSelectionModel;
class ImportDataEditorActions;
class ImportDataEditorToolBar;
class DataSelectorWidget;
class GraphCanvasWidget;

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
    std::string activeCanvasName() const;
    void onImportDialogAccept(DataImportLogic::ImportOutput import_output);
    RealDataStruct convertToRealDataStruct(const std::string& path,
                                           const DataImportLogic::ParsedFileOutptut* import_output,
                                           const int column);

private:
    DataSelectionModel* selectionModel() const;

    ExperimentalDataModel* p_model{nullptr};
    DataViewModel* p_view_model{nullptr};
    ImportDataEditorActions* m_editorActions{nullptr};
    ImportDataEditorToolBar* m_editorToolBar{nullptr};
    DataSelectorWidget* m_dataSelectorWidget{nullptr};
    GraphCanvasWidget* m_graphCanvasWidget{nullptr};
};

#endif // DAREFL_IMPORTDATAWIDGETS_IMPORTDATAEDITOR_H
