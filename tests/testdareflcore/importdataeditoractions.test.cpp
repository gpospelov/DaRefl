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

using namespace ModelView;

//! Tests of ImportDataEditorActions.

class ImportDataEditorActionsTest : public ::testing::Test
{
public:
    ~ImportDataEditorActionsTest();
};

ImportDataEditorActionsTest::~ImportDataEditorActionsTest() = default;

//! Checking initial data for testing.

TEST_F(ImportDataEditorActionsTest, onAddCanvas)
{
    ExperimentalDataModel model;
    ImportDataEditorActions actions(&model);

    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 0);
    actions.onAddCanvas();
    EXPECT_EQ(model.canvasContainer()->canvasItems().size(), 1);
}
