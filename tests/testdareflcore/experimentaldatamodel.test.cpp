// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <darefl/model/item_constants.h>

#include <QSignalSpy>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

//! Tests of ExperimentalDataModel.

class ExperimentalDataModelTest : public ::testing::Test
{
public:
    ~ExperimentalDataModelTest();
    RealDataStruct getRealDataStruct() const;
};

ExperimentalDataModelTest::~ExperimentalDataModelTest() = default;

//! Test the initial state of the model.

TEST_F(ExperimentalDataModelTest, initialState)
{
    ExperimentalDataModel model;

    ASSERT_TRUE(model.canvasContainer() != nullptr);
    EXPECT_EQ(model.canvasContainer()->childrenCount(), 0);
    EXPECT_EQ(model.canvasContainer()->modelType(), ::Constants::CanvasContainerItemType);
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 0);

    ASSERT_TRUE(model.dataContainer() != nullptr);
    EXPECT_EQ(model.dataContainer()->childrenCount(), 0);
    EXPECT_EQ(model.dataContainer()->modelType(), ::Constants::ExperimentalDataContainerItemType);
    EXPECT_EQ(model.dataContainer()->dataItems().size(), 0);
}

//! Adding canvas to the model.

TEST_F(ExperimentalDataModelTest, addCanvas)
{
    ExperimentalDataModel model;

    auto canvas = model.addCanvas();
    ASSERT_TRUE(canvas != nullptr);
    EXPECT_EQ(canvas->graphItems().size(), 0);
    EXPECT_EQ(canvas->modelType(), ::Constants::CanvasItemType);
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 1);
    EXPECT_EQ(model.canvasContainer()->canvasItems(), std::vector<CanvasItem*>() = {canvas});
}

//! Adding graph from the data structure.

TEST_F(ExperimentalDataModelTest, addGraph)
{
    ExperimentalDataModel model;
    std::vector<double> bin_centers{1, 2, 3};
    std::vector<double> bin_values{10, 20, 30};

    RealDataStruct raw_data = {"", bin_centers, "", bin_values, ""};

    auto canvas = model.addCanvas();

    // adding graph, it should appear in canvas
    auto graph = model.addGraph(raw_data, *canvas);
    ASSERT_EQ(canvas->graphItems().size(), 1);
    EXPECT_EQ(canvas->graphItems()[0], graph);

    // graph should have values as defined in the raw_data
    EXPECT_EQ(graph->binCenters(), bin_centers);
    EXPECT_EQ(graph->binValues(), bin_values);

    EXPECT_EQ(model.dataContainer()->childrenCount(), 1);
    std::vector<Data1DItem*> expected_items = {graph->dataItem()};
    EXPECT_EQ(model.dataContainer()->dataItems(), expected_items);
}

//! Removing just added graph.

TEST_F(ExperimentalDataModelTest, removeGraph)
{
    ExperimentalDataModel model;
    std::vector<double> bin_centers{1, 2, 3};
    std::vector<double> bin_values{10, 20, 30};

    RealDataStruct raw_data = {"", bin_centers, "", bin_values, ""};

    auto canvas = model.addCanvas();

    // adding graph
    auto graph = model.addGraph(raw_data, *canvas);

    // removing graph
    model.removeGraph(*graph);

    // should remoive bove graph, and underlying data item
    EXPECT_EQ(canvas->graphItems().size(), 0);
    EXPECT_EQ(model.dataContainer()->dataItems().size(), 0);
}

//! Removing middle graph from the collection.

TEST_F(ExperimentalDataModelTest, removeMiddleGraph)
{
    ExperimentalDataModel model;
    std::vector<double> bin_centers{1, 2, 3};
    std::vector<double> bin_values{10, 20, 30};

    RealDataStruct raw_data = {"", bin_centers, "", bin_values, ""};

    auto canvas = model.addCanvas();

    // adding graph, it should appear in canvas
    auto graph0 = model.addGraph(raw_data, *canvas);
    auto graph1 = model.addGraph(raw_data, *canvas);
    auto graph2 = model.addGraph(raw_data, *canvas);

    // removing graph
    model.removeGraph(*graph1);

    std::vector<GraphItem*> expected_graphs = {graph0, graph2};
    ASSERT_EQ(canvas->graphItems(), expected_graphs);
    std::vector<Data1DItem*> expected_items = {graph0->dataItem(), graph2->dataItem()};
    EXPECT_EQ(model.dataContainer()->dataItems(), expected_items);
}

//! Removing just added graph.

TEST_F(ExperimentalDataModelTest, removeCanvasWithGraph)
{
    ExperimentalDataModel model;
    std::vector<double> bin_centers{1, 2, 3};
    std::vector<double> bin_values{10, 20, 30};

    RealDataStruct raw_data = {"", bin_centers, "", bin_values, ""};

    auto canvas = model.addCanvas();

    // adding graph
    model.addGraph(raw_data, *canvas);

    // removing graph
    model.removeCanvas(*canvas);

    // should remoive bove graph, and underlying data item
    EXPECT_EQ(model.dataContainer()->dataItems().size(), 0);
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 0);
}

//! Merge single canvas into itself. Nothing should happen.

TEST_F(ExperimentalDataModelTest, mergeSingleCanvas)
{
    ExperimentalDataModel model;

    RealDataStruct raw_data = {"", {1}, "", {10}, ""};
    auto canvas = model.addCanvas();
    auto graph = model.addGraph(raw_data, *canvas);

    // removing graph
    model.mergeCanvases(std::vector<CanvasItem*>({canvas}));

    // should remove bove graph, and underlying data item
    EXPECT_EQ(model.dataContainer()->dataItems().size(), 1);
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 1);
    EXPECT_EQ(canvas->graphItems(), std::vector<GraphItem*>({graph}));
}

//! Merge single canvas into itself. Nothing should happen.

TEST_F(ExperimentalDataModelTest, mergeTwoCanvases)
{
    ExperimentalDataModel model;

    RealDataStruct raw_data0 = {"", {1}, "", {10}, ""};
    RealDataStruct raw_data1 = {"", {2}, "", {20}, ""};
    RealDataStruct raw_data2 = {"", {3}, "", {30}, ""};

    auto canvas0 = model.addCanvas();
    auto graph0 = model.addGraph(raw_data0, *canvas0);

    auto canvas1 = model.addCanvas();
    auto graph1 = model.addGraph(raw_data1, *canvas1);
    auto graph2 = model.addGraph(raw_data2, *canvas1);

    // removing graph
    model.mergeCanvases(std::vector<CanvasItem*>({canvas0, canvas1}));

    // should remoive bove graph, and underlying data item
    EXPECT_EQ(model.dataContainer()->dataItems().size(), 3);
    EXPECT_EQ(model.canvasContainer()->canvasItems(), std::vector<CanvasItem*>({canvas0}));
    EXPECT_EQ(canvas0->graphItems(), std::vector<GraphItem*>({graph0, graph1, graph2}));

    EXPECT_EQ(graph0->dataItem()->binCenters(), std::vector<double>({1}));
    EXPECT_EQ(graph1->dataItem()->binCenters(), std::vector<double>({2}));
    EXPECT_EQ(graph2->dataItem()->binCenters(), std::vector<double>({3}));
}

// -----------------------------------------------------------------------------------------
// TODO cleanup below
// -----------------------------------------------------------------------------------------

////! Test the itemIsEditable method
// TEST_F(ExperimentalDataModelTest, itemEditable)
//{
//    ExperimentalDataModel model;

//    EXPECT_EQ(true, model.itemEditable(new GraphItem));
//    EXPECT_EQ(true, model.itemEditable(new CanvasItem));
//    EXPECT_EQ(true, model.itemEditable(new CanvasContainerItem));
//    EXPECT_EQ(false, model.itemEditable(new SessionItem));
//}

////! Test the dragEnabled method
// TEST_F(ExperimentalDataModelTest, dragEnabled)
//{
//    ExperimentalDataModel model;

//    EXPECT_EQ(true, model.dragEnabled(new GraphItem));
//    EXPECT_EQ(true, model.dragEnabled(new CanvasItem));
//    EXPECT_EQ(false, model.dragEnabled(new CanvasContainerItem));
//    EXPECT_EQ(false, model.dragEnabled(new SessionItem));
//}

////! Test the dropEnabled method
// TEST_F(ExperimentalDataModelTest, dropEnabled)
//{
//    ExperimentalDataModel model;

//    EXPECT_EQ(false, model.dropEnabled(new GraphItem));
//    EXPECT_EQ(true, model.dropEnabled(new CanvasItem));
//    EXPECT_EQ(false, model.dropEnabled(new CanvasContainerItem));
//    EXPECT_EQ(false, model.dropEnabled(new SessionItem));
//}

////! test the dragDropItem method with two groups
// TEST_F(ExperimentalDataModelTest, dragDropItemGroup)
//{
//    ExperimentalDataModel model;
//    int default_child_count = CanvasItem().childrenCount();
//    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
//    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

//    CanvasItem* data_group_item_1 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_1 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
//    }

//    CanvasItem* data_group_item_2 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_2 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
//    }

//    EXPECT_EQ(2, root_view_item->childrenCount());
//    EXPECT_EQ(20, root_container_item->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

//    EXPECT_EQ(true, model.dragDropItem(data_group_item_2, data_group_item_1));
//    EXPECT_EQ(1, root_view_item->childrenCount());
//    EXPECT_EQ(20, root_container_item->childrenCount());
//    EXPECT_EQ(20 + default_child_count, data_group_item_1->childrenCount());
//}

////! test the dragDropItem method with graph item
// TEST_F(ExperimentalDataModelTest, dragDropItemGraph)
//{
//    ExperimentalDataModel model;
//    int default_child_count = CanvasItem().childrenCount();
//    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
//    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

//    CanvasItem* data_group_item_1 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_1 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
//    }

//    CanvasItem* data_group_item_2 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_2 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
//    }
//    auto data_children = data_group_item_2->children();
//    std::vector<SessionItem*> graph_items;
//    std::copy_if(data_children.begin(), data_children.end(), std::back_inserter(graph_items),
//                 [](auto item) { return dynamic_cast<GraphItem*>(item); });

//    EXPECT_EQ(2, root_view_item->childrenCount());
//    EXPECT_EQ(20, root_container_item->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

//    EXPECT_EQ(true, model.dragDropItem(graph_items[0], data_group_item_1));
//    EXPECT_EQ(true, model.dragDropItem(graph_items[1], data_group_item_1));
//    EXPECT_EQ(true, model.dragDropItem(graph_items[2], data_group_item_1));

//    EXPECT_EQ(2, root_view_item->childrenCount());
//    EXPECT_EQ(20, root_container_item->childrenCount());
//    EXPECT_EQ(13 + default_child_count, data_group_item_1->childrenCount());
//    EXPECT_EQ(7 + default_child_count, data_group_item_2->childrenCount());
//}

////! test the mergeItems method
// TEST_F(ExperimentalDataModelTest, mergeItems)
//{
//    ExperimentalDataModel model;
//    int default_child_count = CanvasItem().childrenCount();
//    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
//    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

//    CanvasItem* data_group_item_1 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_1 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
//    }

//    CanvasItem* data_group_item_2 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_2 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
//    }

//    CanvasItem* data_group_item_3 = nullptr;
//    for (int i = 0; i < 10; ++i) {
//        data_group_item_3 =
//            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_3);
//    }

//    EXPECT_EQ(3, root_view_item->childrenCount());
//    EXPECT_EQ(30, root_container_item->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());
//    EXPECT_EQ(10 + default_child_count, data_group_item_3->childrenCount());

//    EXPECT_EQ(true, model.mergeItems({data_group_item_1, data_group_item_2, data_group_item_3}));

//    EXPECT_EQ(1, root_view_item->childrenCount());
//    EXPECT_EQ(30, root_container_item->childrenCount());
//    EXPECT_EQ(30 + default_child_count, data_group_item_1->childrenCount());
//}
