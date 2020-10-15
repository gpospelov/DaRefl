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
#include <initializer_list>
#include <vector>

using namespace DataLoader;

//! Tests of ParseUtils.

class ParseUtilsTest : public FolderBasedTest
{
public:
    ParseUtilsTest() : FolderBasedTest("test_ParseUtilsTest") {}
    ~ParseUtilsTest();

    template <typename T = std::string, typename... Args>
    std::vector<T> toStringVector(Args&&... args)
    {
        std::vector<T> v;
        (v.push_back(std::string(args)), ...);
        return v;
    }

    std::vector<std::pair<int, int>>
    toPairVector(std::initializer_list<std::pair<int, int>> list = {})
    {
        return std::vector<std::pair<int, int>>(list.begin(), list.end());
    }
};

ParseUtilsTest::~ParseUtilsTest() = default;

//! Testing function TrimWhitespace

TEST_F(ParseUtilsTest, TrimWhiteSpace)
{
    EXPECT_EQ(TrimWhitespace(""), std::string());
    EXPECT_EQ(TrimWhitespace(" "), std::string());
    EXPECT_EQ(TrimWhitespace("abc"), std::string("abc"));
    EXPECT_EQ(TrimWhitespace(" \t\n abc cde\n"), std::string("abc cde"));
}


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
    EXPECT_TRUE(StringToDouble(" 42").has_value());
    EXPECT_TRUE(StringToDouble(" 42 ").has_value());
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

//! Testing local utility function.

TEST_F(ParseUtilsTest, toStringVector)
{
    std::vector<std::string> expected;

    expected = {};
    EXPECT_EQ(toStringVector(), expected);

    expected = {"a"};
    EXPECT_EQ(toStringVector("a"), expected);

    expected = {"a", "b"};
    EXPECT_EQ(toStringVector("a", "b"), expected);

    expected = {"aaa", "bbb", ""};
    EXPECT_EQ(toStringVector("aaa", "bbb", ""), expected);
}

//! Testing local utility function.

TEST_F(ParseUtilsTest, toPairVector)
{
    std::vector<std::pair<int, int>> expected;

    expected = {};
    EXPECT_EQ(toPairVector(), expected);
    expected = {{1, 2}};
    EXPECT_EQ(toPairVector({{1, 2}}), expected);
    expected = {{1, 2}, {3, 4}};
    EXPECT_EQ(toPairVector({{1, 2}, {3, 4}}), expected);
}

//! Testing SplitString method.
//! Carefully checking that it is reproduces Python behavior, as promised in comments to the method.

TEST_F(ParseUtilsTest, SplitString)
{
    EXPECT_THROW(SplitString("", ""), std::runtime_error);
    EXPECT_EQ(SplitString("", " "), toStringVector());
    EXPECT_EQ(SplitString("", ","), toStringVector());
    EXPECT_EQ(SplitString(" ", " "), toStringVector("", ""));
    EXPECT_EQ(SplitString("a", " "), toStringVector("a"));
    EXPECT_EQ(SplitString("a ", " "), toStringVector("a", ""));

    EXPECT_EQ(SplitString("a", "-"), toStringVector("a"));

    EXPECT_EQ(SplitString("aa", "a"), toStringVector("", "", ""));

    EXPECT_EQ(SplitString("a,b", ","), toStringVector("a", "b"));
    EXPECT_EQ(SplitString("a,b,", ","), toStringVector("a", "b", ""));
    EXPECT_EQ(SplitString(",a,b,", ","), toStringVector("", "a", "b", ""));
    EXPECT_EQ(SplitString("aabbcc", "bb"), toStringVector("aa", "cc"));
}

//! Checking method to expand line numbers
//! "1, 2-4" -> {0, 0}, {1, 3}

TEST_F(ParseUtilsTest, ExpandLineNumberPattern)
{
    EXPECT_EQ(ExpandLineNumberPattern(""), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern(" "), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("aaa"), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("1"), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1"), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 "), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern("42"), toPairVector({{41, 41}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,1"), toPairVector({{0, 0}, {0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern("1,2"), toPairVector({{0, 0}, {1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 , 2 "), toPairVector({{0, 0}, {1, 1}}));

    EXPECT_EQ(ExpandLineNumberPattern("1-1"), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern("1-5"), toPairVector({{0, 4}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,2-3"), toPairVector({{0, 0}, {1, 2}}));
    EXPECT_EQ(ExpandLineNumberPattern("1, 2-3, 42"), toPairVector({{0, 0}, {1, 2}, {41, 41}}));

    // more wrong patterns
    EXPECT_EQ(ExpandLineNumberPattern("1,b"), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern("a,1,b"), toPairVector({{0, 0}}));
    EXPECT_EQ(ExpandLineNumberPattern("a-2"), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("6-5"), toPairVector()); // wrong order
}
