// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUndoStack>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/graphimportdata.h>
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/comboproperty.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/viewmodel/viewmodelutils.h>

namespace
{
template <typename T> std::vector<T*> itemsFromIndexList(const QModelIndexList& indices)
{
    return ModelView::Utils::CastedItems<T>(ModelView::Utils::UniqueItemsFromIndex(indices));
}

const int selected_graph_combo_index = 2; // from graphitem.cpp, "DashLine"
const int default_graph_combo_index = 1;  // from graphitem.cpp, "SolidLine"

} // namespace

ImportDataEditorActions::ImportDataEditorActions(ExperimentalDataModel* model, QObject* parent)
    : QObject(parent), m_dataModel(model)
{
}

void ImportDataEditorActions::setSelectionModel(DataSelectionModel* selection_model)
{
    if (m_selectionModel)
        disconnect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                   &ImportDataEditorActions::onSelectionChanged);

    m_selectionModel = selection_model;

    if (m_selectionModel)
        connect(m_selectionModel, &DataSelectionModel::selectionChanged, this,
                &ImportDataEditorActions::onSelectionChanged);
}

//! Create new canvas and append it to the end of canvas container.

void ImportDataEditorActions::onAddCanvas()
{
    m_dataModel->addCanvas();
}

//! Merge selected canvases. All graphs will appear below canvas selected first.

void ImportDataEditorActions::onMergeCanvases()
{
    m_dataModel->mergeCanvases(m_selectionModel->selectedCanvas());
}

//! Delete currently selected items.

void ImportDataEditorActions::onDeleteItem()
{
    for (auto canvas : m_selectionModel->selectedCanvas())
        m_dataModel->removeCanvas(*canvas);

    for (auto graph : m_selectionModel->selectedGraphs())
        m_dataModel->removeGraph(*graph);
}

void ImportDataEditorActions::onUndo()
{
    if (!m_dataModel->undoStack())
        return;

    m_dataModel->undoStack()->undo();
}

void ImportDataEditorActions::onRedo()
{
    if (!m_dataModel->undoStack())
        return;

    m_dataModel->undoStack()->redo();
}

//! Processes changed selection. Will change line style of selected graph from
//! solid to dashed line.

void ImportDataEditorActions::onSelectionChanged(const QItemSelection& selected,
                                                 const QItemSelection& deselected)
{
    // FIXME refactor code below after PenItem is implemented
    auto selected_graphs = itemsFromIndexList<ModelView::GraphItem>(selected.indexes());
    for (auto graph : selected_graphs) {
        auto pencombo = graph->property<ModelView::ComboProperty>(ModelView::GraphItem::P_PENSTYLE);
        pencombo.setCurrentIndex(selected_graph_combo_index);
        graph->setProperty(ModelView::GraphItem::P_PENSTYLE, pencombo);
    }

    auto deselected_graphs = itemsFromIndexList<ModelView::GraphItem>(deselected.indexes());
    for (auto graph : deselected_graphs) {
        auto pencombo = graph->property<ModelView::ComboProperty>(ModelView::GraphItem::P_PENSTYLE);
        pencombo.setCurrentIndex(default_graph_combo_index);
        graph->setProperty(ModelView::GraphItem::P_PENSTYLE, pencombo);
    }
}
