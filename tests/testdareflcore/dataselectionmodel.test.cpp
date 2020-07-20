// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QDebug>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

//! Tests of DataSelectionModel.

class DataSelectionModelTest : public ::testing::Test
{
public:
    ~DataSelectionModelTest();

    struct TestData {
        ExperimentalDataModel data_model;
        DataViewModel view_model{&data_model};
        DataSelectionModel selection_model{&view_model};
        CanvasContainerItem* container{nullptr};
        CanvasItem* canvas0{nullptr};
        GraphItem* graph_c0_a{nullptr};
        GraphItem* graph_c0_b{nullptr};
        CanvasItem* canvas1{nullptr};
        GraphItem* graph_c1_a{nullptr};
        TestData()
        {
            container = Utils::TopItem<CanvasContainerItem>(&data_model);
            canvas0 = data_model.insertItem<CanvasItem>(container);
            graph_c0_a = data_model.insertItem<GraphItem>(canvas0);
            graph_c0_b = data_model.insertItem<GraphItem>(canvas0);
            canvas1 = data_model.insertItem<CanvasItem>(container);
            graph_c1_a = data_model.insertItem<GraphItem>(canvas1);
            view_model.setRootSessionItem(container);
        }
    };
};

DataSelectionModelTest::~DataSelectionModelTest() = default;

//! Initial state of selection model.

TEST_F(DataSelectionModelTest, initialState)
{
    TestData test_data;
    // checking layout of container with test data
    EXPECT_EQ(test_data.container->size(), 2);

    // checking that no selection exists
    EXPECT_FALSE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedCanvas(), nullptr);
}

//! Select single canvas and check that it was actually selected.

TEST_F(DataSelectionModelTest, selectCanvasItem)
{
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // make canvas0 selected
    test_data.selection_model.selectItem(test_data.canvas0);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 2); // CanvasItem, ViewEmptyItem

    std::vector<SessionItem*> expected = {test_data.canvas0};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    EXPECT_EQ(test_data.selection_model.selectedCanvas(), test_data.canvas0);
}

//! Select single canvas and check that it was actually selected.

TEST_F(DataSelectionModelTest, selectGraph)
{
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // make canvas0 selected
    test_data.selection_model.selectItem(test_data.graph_c0_a);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 2); // GraphItem, LabelItem

    std::vector<SessionItem*> expected = {test_data.graph_c0_a};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // method should report parent of graph as selected canvas
    EXPECT_EQ(test_data.selection_model.selectedCanvas(), test_data.canvas0);
}
