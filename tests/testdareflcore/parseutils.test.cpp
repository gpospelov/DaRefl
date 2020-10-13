// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "folderbasedtest.h"
#include "test_utils.h"
#include <darefl/dataloader2/parseutils.h>

using namespace DataLoader;

//! Tests of ParseUtils.

class ParseUtilsTest :  public FolderBasedTest
{
public:
    ParseUtilsTest() : FolderBasedTest("test_ParseUtilsTest") {}
    ~ParseUtilsTest();

    void create_test_file(const std::string& content) {

    }
};

ParseUtilsTest::~ParseUtilsTest() = default;

//! Testing function StringToDouble.

TEST_F(ParseUtilsTest, StringToDouble)
{
    // not a double
    EXPECT_FALSE(StringToDouble("").has_value());
    EXPECT_FALSE(StringToDouble(" ").has_value());
    EXPECT_FALSE(StringToDouble("a").has_value());
    EXPECT_FALSE(StringToDouble("a b").has_value());

    // not a double: some mixture present
    EXPECT_FALSE(StringToDouble("42a").has_value());
    EXPECT_FALSE(StringToDouble("42.5.5").has_value());

    // not a double: more than one double
    EXPECT_FALSE(StringToDouble("42.5 52").has_value());

    // valid double
    EXPECT_TRUE(StringToDouble("42").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("42").value(), 42.0);
    EXPECT_TRUE(StringToDouble("42.5").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("42.5").value(), 42.5);
    EXPECT_TRUE(StringToDouble("-1.12e-06").has_value());
    EXPECT_DOUBLE_EQ(StringToDouble("-1.12e-06").value(), -1.12e-06);
}

//! Testing ParseSpaceSeparatedDoubles.

TEST_F(ParseUtilsTest, ParseSpaceSeparatedDoubles)
{
    std::vector<double> data;

    EXPECT_TRUE(ParseSpaceSeparatedDoubles("").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles(" ").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles("a").empty());
    EXPECT_TRUE(ParseSpaceSeparatedDoubles("a b").empty());

    ASSERT_EQ(ParseSpaceSeparatedDoubles("4.02").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42aaa").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42aaa")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42aaa").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42aaa")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42,").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,43")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42 ,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 ,43")[0], 42.0);

    ASSERT_EQ(ParseSpaceSeparatedDoubles("42 43").size(), 2u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 43")[0], 42.0);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 43")[1], 43.0);
}

TEST_F(ParseUtilsTest, LoadASCIIFile)
{
    std::string content = {"abc abc\n 123 456\n"};
    auto file_name = TestUtils::CreateTestFile(testPath(), "a.txt", content);

    auto raw_data = LoadASCIIFile(file_name);
    EXPECT_EQ(raw_data.size(), 2u);
    EXPECT_EQ(raw_data[0], std::string("abc abc"));
    EXPECT_EQ(raw_data[1], std::string(" 123 456"));
}

