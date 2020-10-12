// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/dataloader/dataimportdialog.h>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/dataselectorwidget.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/importdataview/graphcanvaswidget.h>
#include <darefl/importdataview/importdataeditor.h>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/importdataview/importdataeditortoolbal.h>
#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/utils/fileutils.h>

using namespace ModelView;

ImportDataEditor::ImportDataEditor(ExperimentalDataModel* model, QWidget* parent)
    : QWidget(parent), p_model(model), p_view_model(new DataViewModel(model)),
      m_editorActions(new ImportDataEditorActions(p_model, this)),
      m_editorToolBar(new ImportDataEditorToolBar(m_editorActions, this)),
      m_dataSelectorWidget(new DataSelectorWidget(p_view_model)),
      m_graphCanvasWidget(new GraphCanvasWidget)
{
    setupLayout();
    setupConnections();

    m_editorActions->setSelectionModel(m_dataSelectorWidget->selectionModel());
    p_view_model->setRootSessionItem(ModelView::Utils::TopItem<CanvasContainerItem>(model));
}

void ImportDataEditor::setupConnections()
{
    // connect toolbar  with this editor
    connect(m_editorToolBar, &ImportDataEditorToolBar::invokeImportDialogRequest, this,
            &ImportDataEditor::invokeImportDialog);
    connect(m_editorToolBar, &ImportDataEditorToolBar::updateViewportRequest,
            [this]() { m_graphCanvasWidget->updateViewport(); });

    // connect selection model with this
    connect(m_dataSelectorWidget, &DataSelectorWidget::selectionChanged, this,
            &ImportDataEditor::selectionChanged);
}

//! Set up the layout of the widget
void ImportDataEditor::setupLayout()
{
    auto main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    auto main_splitter = new QSplitter(this);

    main_splitter->addWidget(m_dataSelectorWidget);
    main_splitter->addWidget(m_graphCanvasWidget);
    main_splitter->setSizes(QList<int>() << 150 << 300);

    main_layout->addWidget(m_editorToolBar);
    main_layout->addWidget(main_splitter);
}

//! Manage a selection change of the treeview
void ImportDataEditor::selectionChanged()
{
    auto selection_model = selectionModel();

    m_graphCanvasWidget->setItem(selection_model->activeCanvas());

    auto items = selection_model->selectedItems();
    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    setMergeEnabled((items.size() > 1) ? (p_model->checkAllGroup(items)) : (false));

    if (items.size() == 0)
        return;

    if (auto viewport = p_model->checkAllGraph(items); viewport) {
        std::vector<ModelView::GraphItem*> graph_items;
        for (std::vector<ModelView::SessionItem*>::iterator it = items.begin(); it != items.end();
             ++it) {
            graph_items.push_back(dynamic_cast<ModelView::GraphItem*>(*it));
        }
        viewport->setVisible(graph_items);
        return;
    }

    auto item = items.at(0);
    if (auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(item); viewport) {
        viewport->setAllVisible();
    } else if (auto graph_item = dynamic_cast<ModelView::GraphItem*>(item); graph_item) {
        auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(graph_item->parent());
        viewport->setVisible(std::vector<ModelView::GraphItem*>{graph_item});
    }
}

//! check itf all items are DataGroupItems, if yes return true
void ImportDataEditor::setMergeEnabled(bool enabled)
{
    auto action = findChild<QAction*>("merge_group_action");
    action->setEnabled(enabled);
}

//! Invoke the data load dialog and connect its state.

void ImportDataEditor::invokeImportDialog()
{
    DataImportGui::DataLoaderDialog dialog(this);
    dialog.setTargets(p_model->availableCanvasesInfo(), activeCanvasName());
    dialog.triggerFileDialog();
    if (dialog.exec() == QDialog::Accepted)
        onImportDialogAccept(dialog.result());
}

//! Find the first selected data group item is present and return his name.

std::string ImportDataEditor::activeCanvasName() const
{
    auto current_canvas = selectionModel()->activeCanvas();
    std::string result = current_canvas ? current_canvas->displayName() : std::string();
    return result;
}

//! Process the accepted state
void ImportDataEditor::onImportDialogAccept(DataImportLogic::ImportOutput import_output)
{
    CanvasContainerItem* canvas_container = p_model->canvasContainer();
    CanvasItem* canvas = dynamic_cast<CanvasItem*>(p_model->findItem(import_output.target()));
    for (auto& path : import_output.keys()) {
        auto parsed_file_output = import_output[path];
        for (int i = 0; i < parsed_file_output->dataCount(); ++i) {
            auto data_struct = convertToRealDataStruct(path, parsed_file_output, i);
            canvas = p_model->addDataToCollection(data_struct, canvas_container, canvas);
        }
    }
    selectionModel()->selectItem(canvas);
}

//! Convert data column to RealDatastructure
RealDataStruct
ImportDataEditor::convertToRealDataStruct(const std::string& path,
                                          const DataImportLogic::ParsedFileOutptut* import_output,
                                          const int column)
{
    auto data_struct = RealDataStruct();

    data_struct.name = Utils::base_name(path);
    data_struct.type = import_output->dataType(column);

    data_struct.axis = import_output->axis();
    data_struct.axis_name = import_output->axisName();
    data_struct.axis_unit = import_output->axisUnit();

    data_struct.data = import_output->data(column);
    data_struct.data_name = import_output->dataName(column);
    data_struct.data_unit = import_output->dataUnit(column);

    return data_struct;
}

DataSelectionModel* ImportDataEditor::selectionModel() const
{
    return m_dataSelectorWidget->selectionModel();
}
