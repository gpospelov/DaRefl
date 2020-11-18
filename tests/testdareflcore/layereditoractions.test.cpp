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
#include <darefl/layereditor/layereditoractions.h>
#include <darefl/layereditor/layerselectionmodel.h>
#include <darefl/layereditor/layerviewmodel.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/sampleitems.h>
#include <darefl/model/samplemodel.h>
#include <mvvm/viewmodel/standardviewitems.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of LayerEditorActions.

class LayerEditorActionsTest : public ::testing::Test
{
public:
    ~LayerEditorActionsTest();

    //! Test data representing MultiLayer with two layers and all machinery around:
    //! ViewModel, SelectionModel and actions.

    struct TestData {
        SampleModel sample_model;
        LayerViewModel view_model{&sample_model};
        LayerSelectionModel selection_model{&view_model};
        LayerEditorActions actions;
        SessionItem* multilayer{nullptr};
        SessionItem* top{nullptr};
        SessionItem* bottom{nullptr};
        TestData()
        {
            actions.setModel(&sample_model);
            actions.setSelectionModel(&selection_model);
            multilayer = sample_model.insertItem<MultiLayerItem>();
            top = sample_model.insertItem<LayerItem>(multilayer);
            bottom = sample_model.insertItem<LayerItem>(multilayer);
            view_model.setRootSessionItem(multilayer);
        }
    };
};

LayerEditorActionsTest::~LayerEditorActionsTest() = default;

//! Checking initial data for testing.

TEST_F(LayerEditorActionsTest, initialState)
{
    TestData test_data;

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 2);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(1), test_data.bottom);

    // checking, that there are no layers selected
    EXPECT_EQ(test_data.selection_model.selectedItems(), std::vector<SessionItem*>());
}

//! Adds new layer after selected layer.

TEST_F(LayerEditorActionsTest, addNewLayerAfterSelection)
{
    TestData test_data;

    // selecting top layer
    test_data.selection_model.selectItem(test_data.top);
    std::vector<SessionItem*> expected = {test_data.top};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // layout
    auto ml_index = QModelIndex();
    auto top_index = test_data.view_model.index(0, 0, ml_index);
    auto bottom_index = test_data.view_model.index(1, 0, ml_index);
    EXPECT_EQ(test_data.view_model.rootItem()->item(), test_data.multilayer);
    EXPECT_EQ(test_data.view_model.itemFromIndex(top_index)->item(),
              test_data.top->getItem(LayerItem::P_NAME));
    EXPECT_EQ(test_data.view_model.itemFromIndex(bottom_index)->item(),
              test_data.bottom->getItem(LayerItem::P_NAME));

    // adding new layer after selection
    test_data.actions.onAddLayer();

    top_index = test_data.view_model.index(0, 0, ml_index);
    bottom_index = test_data.view_model.index(2, 0, ml_index);
    EXPECT_EQ(test_data.view_model.itemFromIndex(top_index)->item(),
              test_data.top->getItem(LayerItem::P_NAME));
    EXPECT_EQ(test_data.view_model.itemFromIndex(bottom_index)->item(),
              test_data.bottom->getItem(LayerItem::P_NAME));

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 3);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(2), test_data.bottom);

    // checking layout of viewmodel

    // checking, that new layer is selected
    expected = {layers.at(1)};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Adds new multi-layer after selected layer.

TEST_F(LayerEditorActionsTest, addNewMultiLayerAfterSelection)
{
    TestData test_data;

    // selecting top layer
    test_data.selection_model.selectItem(test_data.top);

    // adding new layer after selection
    test_data.actions.onAddMultiLayer();

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 3);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(2), test_data.bottom);

    // checking that layer was added
    EXPECT_EQ(layers.at(1)->modelType(), ::Constants::MultiLayerItemType);
    auto sublayers = layers.at(1)->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(sublayers.size(), 2);

    // checking, that new layer is selected
    std::vector<SessionItem*> expected = {layers.at(1)};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Adds new layer when no selection exists.

TEST_F(LayerEditorActionsTest, addNewLayerNoSelection)
{
    TestData test_data;

    // adding new layer when no selection exist
    test_data.actions.onAddLayer();

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 3);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(1), test_data.bottom);

    // checking, that new layer is selected
    std::vector<SessionItem*> expected = {layers.at(2)};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Adds new layer after selected layer.

TEST_F(LayerEditorActionsTest, onRemoveLayer)
{
    TestData test_data;

    // selecting top layer
    test_data.selection_model.selectItem(test_data.top);

    // removing selected top layer
    test_data.actions.onRemove();

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 1);
    EXPECT_EQ(layers.at(0), test_data.bottom);

    // checking, that next layer beneath is selected
    std::vector<SessionItem*> expected = {test_data.bottom};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Move one layer up.

TEST_F(LayerEditorActionsTest, onMoveUp)
{
    TestData test_data;

    // selecting bottom layer
    test_data.selection_model.selectItem(test_data.bottom);

    // moving selected bottom layer up
    test_data.actions.onMoveUp();

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 2);
    EXPECT_EQ(layers.at(0), test_data.bottom);
    EXPECT_EQ(layers.at(1), test_data.top);

    // checking, that former bottom layer is stil selected
    std::vector<SessionItem*> expected = {test_data.bottom};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // moving up once again, nothing should change
    test_data.actions.onMoveUp();
    EXPECT_EQ(layers.at(0), test_data.bottom);
    EXPECT_EQ(layers.at(1), test_data.top);
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Move one layer up.

TEST_F(LayerEditorActionsTest, onMoveDown)
{
    TestData test_data;

    // selecting top layer
    test_data.selection_model.selectItem(test_data.top);

    // moving selected top layer down
    test_data.actions.onMoveDown();

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 2);
    EXPECT_EQ(layers.at(0), test_data.bottom);
    EXPECT_EQ(layers.at(1), test_data.top);

    // checking, that former top layer is stil selected
    std::vector<SessionItem*> expected = {test_data.top};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // moving down once again, nothing should change
    test_data.actions.onMoveDown();
    EXPECT_EQ(layers.at(0), test_data.bottom);
    EXPECT_EQ(layers.at(1), test_data.top);
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}
