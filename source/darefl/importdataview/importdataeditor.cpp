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
#include <darefl/dataloader2/dataloaderdialog_v2.h>
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
#include <mvvm/utils/containerutils.h>
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
    DataLoaderDialogV2 dialog(this);

    auto [names, index] = canvasInfo();
    dialog.setTargetCanvas(names, index);

    dialog.invokeFileSelectorDialog();

    if (dialog.exec() == QDialog::Accepted) {
        auto canvases = Utils::FindItems<CanvasItem>(p_model);
        CanvasItem* target =
            dialog.targetCanvasIndex() >= 0 ? canvases[dialog.targetCanvasIndex()] : nullptr;

        onImportDialogAccept2(dialog.importedData(), target);
    }
}

std::pair<std::vector<std::string>, int> ImportDataEditor::canvasInfo() const
{
    std::vector<std::string> names;
    auto canvases = Utils::FindItems<CanvasItem>(p_model);
    auto current_canvas = selectionModel()->activeCanvas();
    std::transform(canvases.begin(), canvases.end(), std::back_inserter(names),
                   [](auto x) { return x->displayName(); });
    return std::make_pair(names, ModelView::Utils::IndexOfItem(canvases, current_canvas));
}

//! Find the first selected data group item is present and return his name.

std::string ImportDataEditor::activeCanvasName() const
{
    auto current_canvas = selectionModel()->activeCanvas();
    std::string result = current_canvas ? current_canvas->displayName() : std::string();
    return result;
}

void ImportDataEditor::onImportDialogAccept2(const std::vector<RealDataStruct>& experimental_data,
                                             CanvasItem* canvas)
{
    CanvasContainerItem* canvas_container = p_model->canvasContainer();
    for (auto& data : experimental_data)
        canvas = p_model->addDataToCollection(data, canvas_container, canvas);
    selectionModel()->selectItem(canvas);
}

DataSelectionModel* ImportDataEditor::selectionModel() const
{
    return m_dataSelectorWidget->selectionModel();
}
