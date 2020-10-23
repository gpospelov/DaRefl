// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_PARSEUTILS_H
#define DAREFL_DATALOADER2_PARSEUTILS_H

#include <darefl/dataloader/dataloader_types.h>
#include <optional>

class RealDataStruct;

namespace DataLoader
{

//! Parses string for double values and returns result as a vector.
//! All non-numeric symbols are ingored.
std::vector<double> ParseSpaceSeparatedDoubles(const std::string& str);

//! Parses string for double values and stores result in a vector.
//! All non-numeric symbols are ingored.
void ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result);

//! Returns string after trimming whitespace surrounding.
//! Tabs and new line includcolumn_infoed.
std::string TrimWhitespace(const std::string& str);

//! Converts string to double value and returns it in the form of optional.
//! Strict: requires that string represents exactly one double and contains no other literals.
std::optional<double> StringToDouble(const std::string& str);

//! Loads ASCII file, returns it in the form of vector of strings.
std::vector<std::string> LoadASCIIFile(const std::string& file_name);

//! Split string on substring using given delimeter. Reproduces Python's str.split() behavior.
std::vector<std::string> SplitString(const std::string& str, const std::string& delimeter);

//! Expands string representing line number pattern to inclusive pairs of line numbers.
//! "1" will be expanded to { {1, 1} }, "1, 3-5" will be expanded to { {1, 1}, {3, 5} }
std::vector<std::pair<int, int>> ExpandLineNumberPattern(const std::string& pattern);

//! Removes repeating spaces for a string.
std::string RemoveRepeatedSpaces(std::string str);

//! Creates a callback to define if given line number satisfies line number pattern.
//! "1, 4-6" will accept numbers {1, 4, 5, 6} and will refuse all others.
accept_int_t CreateLineNumberPatternValidator(const std::string& pattern);

//! Creates a callback to define if given line has a valid content for further parsing.
//! Empty lines and lines starting from a given prefix will be excluded.
accept_string_t CreateLineContentBaseValidator(const std::string& prefix_to_exclude);

//! Creates line splitter based on separator.
line_splitter_t CreateSeparatorBasedSplitter(const std::string& separator);

//! Returns string representing original 'line' wrapped in 'div' tag.
std::string AddHtmlDivTag(const std::string& line);

//! Returns string representing original 'line' wrapped in html color tag.
std::string AddHtmlColorTag(const std::string& line, const std::string& color);

//! Returns string representing original 'line' wrapped in 'div' tag.
std::string AddHtmlBackgroundTag(const std::string& line, const std::string& color);

//! Returns string representing original 'line', where 'parts' are surrounded with color tag.
std::string AddHtmlColorTagToParts(const std::string& line, const std::vector<std::string>& parts,
                                   const std::string& color_parts, const std::string& color_rest);

//! Extracts double values from two columns of a string array.
//! The row must be valid: string value must represent single double for both target columns,
//! rows should have enough columns. If a row is invalid, it will be skipped, so resulting arrays
//! have always the same length.

std::pair<std::vector<double>, std::vector<double>>
ExtractTwoColumns(const std::vector<std::vector<std::string>>& text_data, size_t col1, size_t col2);

//! Pack ColumnInfo into pairs representing {AxisType, IntensityType}.
//! For the moment we expect that only one column with AxisType exists. Number of intensity columns
//! can be arbitrary.

std::vector<std::pair<ColumnInfo, ColumnInfo>>
CreateGraphInfoPairs(const std::vector<ColumnInfo>& column_info);

//! Creates structure from text data.

RealDataStruct CreateData(const std::vector<std::vector<std::string>>& text_data,
                          const ColumnInfo& axis, const ColumnInfo& intensity);

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
