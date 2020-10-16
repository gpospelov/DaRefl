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
#include <darefl/dataloader2/defaultparser.h>
#include <darefl/dataloader2/dataloader_types.h>

using namespace DataLoader;

//! Test DefaultParser.

class DefaultParserTest : public ::testing::Test
{
public:
    ~DefaultParserTest();
};

DefaultParserTest::~DefaultParserTest() = default;

TEST_F(DefaultParserTest, initialState)
{
    ParserOptions options = {"#", ",", ""}; // prefix, separator, line pattern
    std::vector<std::string> raw_data = {
        "# comment"
    };

    EXPECT_EQ(0, 0);
}

//TEST_F(DefaultParserTest, initialState)
//{
//    ParserOptions options = {"#", ",", ""}; // prefix, separator, line pattern
//    std::vector<std::string> raw_data = {
//        "# comment"
//    };

//    EXPECT_EQ(0, 0);
//}
