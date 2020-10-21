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
#include <darefl/dataloader2/importtableheader.h>

using namespace DataLoader;

//! Test the data column item
class ImportTableHeaderTest : public ::testing::Test
{
public:
    ~ImportTableHeaderTest();
};

ImportTableHeaderTest::~ImportTableHeaderTest() = default;

TEST_F(ImportTableHeaderTest, initialState)
{
    EXPECT_EQ(1, 1);
}
