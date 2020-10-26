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
#include <darefl/dataloader/dataloaderdialog.h>
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
    : QWidget(parent), m_dataModel(model), m_viewModel(new DataViewModel(model)),
      m_editorActions(new ImportDataEditorActions(m_dataModel, this)),
      m_editorToolBar(new ImportDataEditorToolBar(m_editorActions, this)),
      m_dataSelectorWidget(new DataSelectorWidget(m_viewModel)),
      m_graphCanvasWidget(new GraphCanvasWidget)
{
    setupLayout();
    setupConnections();

    m_editorActions->setSelectionModel(m_dataSelectorWidget->selectionModel());
    m_viewModel->setRootSessionItem(ModelView::Utils::TopItem<CanvasContainerItem>(model));
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
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto splitter = new QSplitter;
    splitter->addWidget(m_dataSelectorWidget);
    splitter->addWidget(m_graphCanvasWidget);
    splitter->setSizes(QList<int>() << 150 << 300);

    layout->addWidget(m_editorToolBar);
    layout->addWidget(splitter);
}

//! Manage a selection change of the treeview
void ImportDataEditor::selectionChanged()
{
    auto selection_model = selectionModel();

    m_graphCanvasWidget->setItem(selection_model->activeCanvas());

    auto items = selection_model->selectedItems();
    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    setMergeEnabled((items.size() > 1) ? (m_dataModel->checkAllGroup(items)) : (false));

    if (items.size() == 0)
        return;

    if (auto viewport = m_dataModel->checkAllGraph(items); viewport) {
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
    DataLoaderDialog dialog(this);

    auto [names, index] = canvasInfo();
    dialog.setTargetCanvas(names, index);

    dialog.invokeFileSelectorDialog();

    if (dialog.exec() == QDialog::Accepted) {
        auto canvases = Utils::FindItems<CanvasItem>(m_dataModel);
        CanvasItem* target =
            dialog.targetCanvasIndex() >= 0 ? canvases[dialog.targetCanvasIndex()] : nullptr;

        onImportDialogAccept(dialog.importedData(), target);
    }
}

//! Returns vector of canvas display name together with index of currently selected canvas.

std::pair<std::vector<std::string>, int> ImportDataEditor::canvasInfo() const
{
    std::vector<std::string> names;
    auto canvases = Utils::FindItems<CanvasItem>(m_dataModel);
    auto current_canvas = selectionModel()->activeCanvas();
    std::transform(canvases.begin(), canvases.end(), std::back_inserter(names),
                   [](auto x) { return x->displayName(); });
    return std::make_pair(names, ModelView::Utils::IndexOfItem(canvases, current_canvas));
}

void ImportDataEditor::onImportDialogAccept(const std::vector<RealDataStruct>& experimental_data,
                                            CanvasItem* canvas)
{
    CanvasContainerItem* canvas_container = m_dataModel->canvasContainer();
    for (auto& data : experimental_data)
        canvas = m_dataModel->addDataToCollection(data, canvas_container, canvas);
    selectionModel()->selectItem(canvas);
}

DataSelectionModel* ImportDataEditor::selectionModel() const
{
    return m_dataSelectorWidget->selectionModel();
}
