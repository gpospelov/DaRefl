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

namespace ModelView
{
class SessionItem;
class GraphCanvas;
class GraphViewportItem;
class TopItemsTreeView;
class PropertyTreeView;
} // namespace ModelView

namespace DataImportLogic
{
class ImportOutput;
class ParsedFileOutptut;
} // namespace DataImportLogic

class ExperimentalDataModel;
class QTreeView;
class QBoxLayout;
class RealDataStruct;
class DataSelectionModel;
class DataViewModel;
class ImportDataEditorActions;
class ImportDataEditorToolBar;

//! Main editor to import user data.

class ImportDataEditor : public QWidget
{
    Q_OBJECT
public:
    ImportDataEditor(ExperimentalDataModel* model, QWidget* parent = nullptr);

private:
    void setupToolBar();
    void setupViews();
    void setupLayout();

    void selectionChanged();
    void setMergeEnabled(bool enabled);

    void invokeImportDialog();
    std::string selectedDataGroupItem() const;
    void onImportDialogAccept(DataImportLogic::ImportOutput import_output);
    RealDataStruct convertToRealDataStruct(const std::string& path,
                                           const DataImportLogic::ParsedFileOutptut* import_output,
                                           const int column);
    void resetAll();

private:
    QTreeView* p_tree_view{nullptr};
    ExperimentalDataModel* p_model{nullptr};
    DataViewModel* p_view_model{nullptr};
    DataSelectionModel* p_data_selection_model{nullptr};
    ImportDataEditorActions* m_editorActions{nullptr};
    ImportDataEditorToolBar* m_editorToolBar{nullptr};
    ModelView::PropertyTreeView* p_property_tree{nullptr};
    ModelView::GraphCanvas* p_graph_canvas{nullptr};
};

#endif // DAREFL_IMPORTDATAWIDGETS_IMPORTDATAEDITOR_H
