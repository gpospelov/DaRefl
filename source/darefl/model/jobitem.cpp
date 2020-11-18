// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/standarditems/plottableitems.h>

using namespace ModelView;

namespace
{
const int row_sim_graph = 0;
const int row_reference_graph = 1;

GraphItem* create_reference_graph(JobItem* item)
{
    auto model = item->model();
    return model->insertItem<GraphItem>(item->specularViewport(),
                                        {ViewportItem::T_ITEMS, row_reference_graph});
}

//! Creates viewport and data properties. Creates graph, adds data to the graph, and graph
//! to viewport.
//! TODO consider to replace it with classes, when JobItem structure becomes clear.

template <typename Data, typename Graph, typename Viewport>
void initViewport(CompoundItem* item, const std::string& data_name,
                  const std::string& viewport_name)
{
    auto data = item->addProperty<Data>(data_name);
    auto viewport = item->addProperty<Viewport>(viewport_name);
    auto graph = std::make_unique<GraphItem>();
    graph->setDataItem(data);
    viewport->insertItem(graph.release(), {ViewportItem::T_ITEMS, 0});
}

} // namespace

SLDCanvasItem::SLDCanvasItem() : GraphViewportItem(::Constants::SLDCanvasItemType) {}

std::pair<double, double> SLDCanvasItem::data_yaxis_range() const
{
    auto [ymin, ymax] = GraphViewportItem::data_yaxis_range();
    double range = ymax - ymin;
    return {ymin - range / 10.0, ymax + range / 10.0};
}

// ----------------------------------------------------------------------------

JobItem::JobItem() : ModelView::CompoundItem(::Constants::JobItemType)
{
    setup_sld_viewport();
    setup_specular_viewport();
    setup_diff_viewport();
}

Data1DItem* JobItem::sldData() const
{
    return item<Data1DItem>(P_SLD_DATA);
}

SLDCanvasItem* JobItem::sldViewport() const
{
    return item<SLDCanvasItem>(P_SLD_VIEWPORT);
}

Data1DItem* JobItem::specularData() const
{
    return item<Data1DItem>(P_SPECULAR_DATA);
}

CanvasItem* JobItem::specularViewport() const
{
    return item<CanvasItem>(P_SPECULAR_VIEWPORT);
}

CanvasItem* JobItem::diffViewport() const
{
    return item<CanvasItem>(P_DIFF_VIEWPORT);
}

//! Updates reference graph in specular viewport from external graph.
//! External graph represents user imported data, it will be used to
//! is comming from another viewport (i.e. containing user imported data),
//! and it is used

void JobItem::updateReferenceGraph(const GraphItem* graph)
{
    if (graph)
        setupReferenceGraphFrom(graph);
    else
        removeReferenceGraph();
}

//! Returns specular graph.

GraphItem* JobItem::specularGraph() const
{
    auto graphs = specularViewport()->graphItems();
    return graphs.size() >= 0 ? graphs.at(row_sim_graph) : nullptr;
}

//! Returns reference graph, if exists. It represents imported user data from ExperimentalScanItem.
//! Here it is stored in SpecularViewport.

GraphItem* JobItem::referenceGraph() const
{
    auto graphs = specularViewport()->graphItems();
    return graphs.size() > 1 ? graphs.at(row_reference_graph) : nullptr;
}

void JobItem::setupReferenceGraphFrom(const GraphItem* graph)
{
    auto reference_graph = referenceGraph() ? referenceGraph() : create_reference_graph(this);
    reference_graph->setFromGraphItem(graph);
}

//! Removes reference graph from specular viewport.

void JobItem::removeReferenceGraph()
{
    if (auto reference_graph = referenceGraph(); reference_graph)
        ModelView::Utils::DeleteItemFromModel(reference_graph);
}

void JobItem::setup_sld_viewport()
{
    initViewport<Data1DItem, GraphItem, SLDCanvasItem>(this, P_SLD_DATA, P_SLD_VIEWPORT);
}

//! Setups a specular viewport together with a single graph in it and corresponding data item.
//! Intended to store simulated specular curve, and possibly reference graphs.

void JobItem::setup_specular_viewport()
{
    initViewport<Data1DItem, GraphItem, CanvasItem>(this, P_SPECULAR_DATA, P_SPECULAR_VIEWPORT);
    auto graph = specularGraph();
    auto pen = graph->item<PenItem>(GraphItem::P_PEN);
    pen->setProperty(PenItem::P_COLOR, QColor(Qt::blue));
}

//! Setups viewport, difference graph, and its underlying data to show the difference between
//! simulated and reference curves.

void JobItem::setup_diff_viewport()
{
    initViewport<Data1DItem, GraphItem, CanvasItem>(this, P_DIFF_DATA, P_DIFF_VIEWPORT);
}
