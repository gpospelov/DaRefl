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
#include <darefl/importdataview/importdataeditoractions.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/importdataview/dataselectionmodel.h>
#include <darefl/model/experimentaldata_types.h>
#include <mvvm/model/modelutils.h>

using namespace ModelView;

//! Tests of ImportDataEditorActions.

class ImportDataEditorActionsTest : public ::testing::Test
{
public:
    ~ImportDataEditorActionsTest();

    struct TestData {
        ExperimentalDataModel data_model;
        DataViewModel view_model{&data_model};
        DataSelectionModel selection_model{&view_model};
        CanvasItem* canvas0{nullptr};
        ImportDataEditorActions actions{&data_model};
        TestData()
        {
            canvas0 = data_model.addCanvas();

            RealDataStruct raw_data = {"", "", {42}, "", "", {42}, "", ""};
            data_model.addGraph(raw_data, *canvas0);

            view_model.setRootSessionItem(data_model.canvasContainer());
            actions.setSelectionModel(&selection_model);
        }
    };

};

ImportDataEditorActionsTest::~ImportDataEditorActionsTest() = default;

//! Checks onAddCanvas.

TEST_F(ImportDataEditorActionsTest, onAddCanvas)
{
    ExperimentalDataModel model;
    ImportDataEditorActions actions(&model);

    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 0);
    actions.onAddCanvas();
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 1);
}

//! Checks onAddCanvas.

TEST_F(ImportDataEditorActionsTest, onDeleteItem)
{
    TestData test_data;
    EXPECT_EQ(test_data.data_model.canvasContainer()->canvasItems().size(), 1);
    EXPECT_EQ(test_data.data_model.dataContainer()->dataItems().size(), 1);

    test_data.selection_model.selectItem(test_data.canvas0);

    test_data.actions.onDeleteItem();

    EXPECT_EQ(test_data.data_model.canvasContainer()->canvasItems().size(), 0);
    EXPECT_EQ(test_data.data_model.dataContainer()->dataItems().size(), 0);
}
