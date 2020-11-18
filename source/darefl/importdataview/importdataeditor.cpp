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
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/utils/containerutils.h>

using namespace ModelView;

ImportDataEditor::ImportDataEditor(ExperimentalDataModel* model, QWidget* parent)
    : QWidget(parent)
    , m_dataModel(model)
    , m_viewModel(new DataViewModel(model))
    , m_editorActions(new ImportDataEditorActions(m_dataModel, this))
    , m_editorToolBar(new ImportDataEditorToolBar(m_editorActions, this))
    , m_dataSelectorWidget(new DataSelectorWidget(m_viewModel))
    , m_graphCanvasWidget(new GraphCanvasWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto splitter = new QSplitter;
    splitter->addWidget(m_dataSelectorWidget);
    splitter->addWidget(m_graphCanvasWidget);
    splitter->setSizes(QList<int>() << 150 << 300);

    layout->addWidget(m_editorToolBar);
    layout->addWidget(splitter);

    m_editorActions->setSelectionModel(m_dataSelectorWidget->selectionModel());
    m_viewModel->setRootSessionItem(model->canvasContainer());

    setupConnections();
}

void ImportDataEditor::setupConnections()
{
    // connect toolbar  with this editor
    connect(m_editorToolBar, &ImportDataEditorToolBar::invokeImportDialogRequest, this,
            &ImportDataEditor::invokeImportDialog);
    connect(m_editorToolBar, &ImportDataEditorToolBar::updateViewportRequest,
            [this]() { m_graphCanvasWidget->updateViewport(); });

    // connect selection model with this
    auto on_selection_changed = [this]() {
        m_graphCanvasWidget->setItem(selectionModel()->activeCanvas());
    };
    connect(m_dataSelectorWidget, &DataSelectorWidget::selectionChanged, on_selection_changed);
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

        onImportDialogAccept(dialog.graphImportData(), target);
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

void ImportDataEditor::onImportDialogAccept(const std::vector<GraphImportData>& graph_data,
                                            CanvasItem* canvas)
{
    if (!canvas)
        canvas = m_dataModel->addCanvas();
    for (auto& data : graph_data)
        m_dataModel->addGraph(data, *canvas);
    selectionModel()->selectItem(canvas);
}

DataSelectionModel* ImportDataEditor::selectionModel() const
{
    return m_dataSelectorWidget->selectionModel();
}
