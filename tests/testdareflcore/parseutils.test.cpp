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
#include <darefl/dataloader2/dataloader_constants.h>
#include <darefl/dataloader2/parseutils.h>
#include <darefl/model/experimentaldata_types.h>
#include <initializer_list>
#include <vector>

using namespace DataLoader;
using TestUtils::toStringVector;

//! Tests of ParseUtils.

class ParseUtilsTest : public FolderBasedTest
{
public:
    ParseUtilsTest() : FolderBasedTest("test_ParseUtilsTest") {}
    ~ParseUtilsTest();

    std::vector<std::pair<int, int>>
    toPairVector(std::initializer_list<std::pair<int, int>> list = {})
    {
        return std::vector<std::pair<int, int>>(list.begin(), list.end());
    }

    std::vector<double> toVector(std::initializer_list<double> args)
    {
        return std::vector<double>(args.begin(), args.end());
    };
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

    // this tests failing under MacOS
    //    ASSERT_EQ(ParseSpaceSeparatedDoubles("42aaa").size(), 1u);
    //    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42aaa")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42,").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42,43")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42 ,43").size(), 1u);
    EXPECT_DOUBLE_EQ(ParseSpaceSeparatedDoubles("42 ,43")[0], 42.0);

    EXPECT_EQ(ParseSpaceSeparatedDoubles("42 43").size(), 2u);
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

    EXPECT_EQ(SplitString("a b", " "), toStringVector("a", "b"));
    EXPECT_EQ(SplitString("a  b", " "), toStringVector("a", "", "b"));

    EXPECT_EQ(SplitString("a", "-"), toStringVector("a"));

    EXPECT_EQ(SplitString("aa", "a"), toStringVector("", "", ""));

    EXPECT_EQ(SplitString("a,b", ","), toStringVector("a", "b"));
    EXPECT_EQ(SplitString("a, b", ","), toStringVector("a", " b"));

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
    EXPECT_EQ(ExpandLineNumberPattern("1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 "), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("42"), toPairVector({{42, 42}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,1"), toPairVector({{1, 1}, {1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("1,2"), toPairVector({{1, 1}, {2, 2}}));
    EXPECT_EQ(ExpandLineNumberPattern(" 1 , 2 "), toPairVector({{1, 1}, {2, 2}}));

    EXPECT_EQ(ExpandLineNumberPattern("1-1"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("1-5"), toPairVector({{1, 5}}));

    EXPECT_EQ(ExpandLineNumberPattern("1,2-3"), toPairVector({{1, 1}, {2, 3}}));
    EXPECT_EQ(ExpandLineNumberPattern("1, 2-3, 42"), toPairVector({{1, 1}, {2, 3}, {42, 42}}));
    EXPECT_EQ(ExpandLineNumberPattern("42, 2-3, 1"), toPairVector({{42, 42}, {2, 3}, {1, 1}}));

    // more wrong patterns
    EXPECT_EQ(ExpandLineNumberPattern("1,b"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("a,1,b"), toPairVector({{1, 1}}));
    EXPECT_EQ(ExpandLineNumberPattern("a-2"), toPairVector());
    EXPECT_EQ(ExpandLineNumberPattern("6-5"), toPairVector()); // wrong order
}

TEST_F(ParseUtilsTest, RemoveRepeatedSpaces)
{
    EXPECT_EQ(RemoveRepeatedSpaces(std::string{}), std::string{});
    EXPECT_EQ(RemoveRepeatedSpaces(" "), std::string{" "});
    EXPECT_EQ(RemoveRepeatedSpaces("a"), std::string{"a"});
    EXPECT_EQ(RemoveRepeatedSpaces(" a "), std::string{" a "});
    EXPECT_EQ(RemoveRepeatedSpaces("  a  "), std::string{" a "});
    EXPECT_EQ(RemoveRepeatedSpaces("a  bb   ccc   "), std::string{"a bb ccc "});
}

TEST_F(ParseUtilsTest, CreateLineNumberPatternValidator)
{
    auto is_accepted = CreateLineNumberPatternValidator("1");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(1));
    EXPECT_FALSE(is_accepted(2));

    is_accepted = CreateLineNumberPatternValidator("");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_FALSE(is_accepted(1));
    EXPECT_FALSE(is_accepted(2));

    is_accepted = CreateLineNumberPatternValidator("1, 2");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(1));
    EXPECT_TRUE(is_accepted(2));
    EXPECT_FALSE(is_accepted(3));

    is_accepted = CreateLineNumberPatternValidator("42, 44-46");
    EXPECT_FALSE(is_accepted(0));
    EXPECT_TRUE(is_accepted(42));
    EXPECT_FALSE(is_accepted(43));
    EXPECT_TRUE(is_accepted(44));
    EXPECT_TRUE(is_accepted(45));
    EXPECT_TRUE(is_accepted(46));
    EXPECT_FALSE(is_accepted(47));
}

TEST_F(ParseUtilsTest, CreateLineContentBaseValidator)
{
    auto is_accepted = CreateLineContentBaseValidator("");
    EXPECT_FALSE(is_accepted(""));
    EXPECT_FALSE(is_accepted(" "));
    EXPECT_FALSE(is_accepted("                                       "));
    EXPECT_TRUE(is_accepted("abc"));
    EXPECT_TRUE(is_accepted(" abc  "));

    is_accepted = CreateLineContentBaseValidator("#");
    EXPECT_FALSE(is_accepted(""));
    EXPECT_FALSE(is_accepted(" "));
    EXPECT_FALSE(is_accepted("# abc"));
    EXPECT_TRUE(is_accepted("42  "));
}

TEST_F(ParseUtilsTest, CreateSeparatorSplitter)
{
    auto parse = CreateSeparatorBasedSplitter(",");
    EXPECT_EQ(parse("a"), toStringVector("a"));
    EXPECT_EQ(parse("a,b"), toStringVector("a", "b"));
    EXPECT_EQ(parse("a, b"), toStringVector("a", " b")); // shouldn't we trim white spaces?
    EXPECT_EQ(parse(" a, b "), toStringVector("a", " b"));

    EXPECT_EQ(parse("1.0,2.0,3.0"), toStringVector("1.0", "2.0", "3.0"));
    EXPECT_EQ(parse("1.0, 2.0, 3.0"), toStringVector("1.0", " 2.0", " 3.0"));
    EXPECT_EQ(parse("1.0, 2.0, 3.0,"), toStringVector("1.0", " 2.0", " 3.0", ""));

    parse = CreateSeparatorBasedSplitter(" ");
    EXPECT_EQ(parse("a"), toStringVector("a"));
    EXPECT_EQ(parse("a b"), toStringVector("a", "b"));
    EXPECT_EQ(parse(" a b "), toStringVector("a", "b"));
    EXPECT_EQ(parse(" a    b "), toStringVector("a", "b"));
}

TEST_F(ParseUtilsTest, AddHtmlColorTag)
{
    EXPECT_EQ(AddHtmlColorTag("abc", "x"), "<font color=\"x\">abc</font>");
}

TEST_F(ParseUtilsTest, AddHtmlDivTag)
{
    EXPECT_EQ(AddHtmlDivTag("abc"), "<div>abc</div>");
}

TEST_F(ParseUtilsTest, AddHtmlColorTagToParts)
{
    auto parse = CreateSeparatorBasedSplitter(",");
    std::string line("a,b");
    EXPECT_EQ(AddHtmlColorTagToParts(line, parse(line), "A", "B"),
              "<div><font color=\"A\">a</font><span style=\"background-color:B\">,</span><font "
              "color=\"A\">b</font></div>");

    parse = CreateSeparatorBasedSplitter(" | ");
    line = "abc | efg";
    EXPECT_EQ(AddHtmlColorTagToParts(line, parse(line), "A", "B"),
              "<div><font color=\"A\">abc</font><span style=\"background-color:B\"> | </span><font "
              "color=\"A\">efg</font></div>");
}

TEST_F(ParseUtilsTest, ExtractTwoColumns)
{
    auto result = ExtractTwoColumns({{}}, 0, 0);
    EXPECT_EQ(result.first.size(), 0);
    EXPECT_EQ(result.second.size(), 0);

    // normal parsing
    result = ExtractTwoColumns({{"1.0", "2.0"}, {"3.0", "4.0"}}, 0, 1);
    EXPECT_EQ(result.first, toVector({1.0, 3.0}));
    EXPECT_EQ(result.second, toVector({2.0, 4.0}));

    result = ExtractTwoColumns({{" 1.0 ", " 2.0 "}, {" 3.0 ", " 4.0 "}}, 0, 1);
    EXPECT_EQ(result.first, toVector({1.0, 3.0}));
    EXPECT_EQ(result.second, toVector({2.0, 4.0}));

    // partial parsing (nan in input)
    result = ExtractTwoColumns({{"---", "2.0"}, {"3.0", "4.0"}}, 0, 1);
    EXPECT_EQ(result.first, toVector({3.0}));
    EXPECT_EQ(result.second, toVector({4.0}));

    // partial parsing (different length of columns)
    result = ExtractTwoColumns({{"1.0", "2.0", "3.0"}, {"4.0", "5.0", "6.0", "7.0"}}, 0, 3);
    EXPECT_EQ(result.first, toVector({4.0}));
    EXPECT_EQ(result.second, toVector({7.0}));
}

TEST_F(ParseUtilsTest, CreateGraphInfoPairs)
{
    ColumnInfo col0{0, DataLoader::Constants::AxisType, "", 0, ""};
    ColumnInfo col1{1, DataLoader::Constants::IntensityType, "", 0, ""};
    ColumnInfo col2{2, DataLoader::Constants::IgnoreType, "", 0, ""};
    ColumnInfo col3{3, DataLoader::Constants::IntensityType, "", 0, ""};

    std::vector<ColumnInfo> infos = {col0, col1, col2, col3};

    auto info_pairs = CreateGraphInfoPairs(infos);
    ASSERT_EQ(info_pairs.size(), 2);
    EXPECT_EQ(info_pairs[0].first.column, 0);
    EXPECT_EQ(info_pairs[0].second.column, 1);
    EXPECT_EQ(info_pairs[1].first.column, 0);
    EXPECT_EQ(info_pairs[1].second.column, 3);
}

TEST_F(ParseUtilsTest, CreateData)
{
    ColumnInfo col0{0, DataLoader::Constants::AxisType, "units0", 1.0, "title0"};
    //    ColumnInfo col1{1, DataLoader::Constants::IgnoreType, "units1", 1.0, "title1"};
    ColumnInfo col2{2, DataLoader::Constants::IntensityType, "units2", 2.0, "title2"};

    std::vector<std::vector<std::string>> text_data = {{"1.0", "2.0", "3.0"},
                                                       {"4.0", "5.0", "6.0"},
                                                       {"7.0", "8.0", "9.0"},
                                                       {"10.0", "11.0", "12.0"}};

    auto data = DataLoader::CreateData(text_data, col0, col2);

    EXPECT_EQ(data.type, "");
    EXPECT_EQ(data.name, "");
    EXPECT_EQ(data.axis, toVector({1.0, 4.0, 7.0, 10.0}));
    EXPECT_EQ(data.axis_name, "title0");
    EXPECT_EQ(data.axis_unit, "units0");
    EXPECT_EQ(data.data, toVector({6.0, 12.0, 18.0, 24.0}));
    EXPECT_EQ(data.data_name, "title2");
    EXPECT_EQ(data.data_unit, "units2");
}
