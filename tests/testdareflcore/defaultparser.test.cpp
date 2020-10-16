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
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/defaultparser.h>

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
    DefaultParser parser({});

    EXPECT_EQ(parser.totalLineCount(), 0);
    EXPECT_EQ(parser.dataRowCount(), 0);
}

 TEST_F(DefaultParserTest, parseScenario1)
{
    DefaultParser parser({"#", ",", ""});  // prefix, separator, line pattern

    std::vector<std::string> raw_data = {
        "# comment",
        "1, 2, 3"
    };

    parser.setRawData(raw_data);
    EXPECT_EQ(parser.totalLineCount(), 2);
    EXPECT_EQ(parser.dataRowCount(), 0);

    parser.parse();
//    EXPECT_EQ(parser.totalLineCount(), 2);
//    EXPECT_EQ(parser.dataRowCount(), 1);

}
