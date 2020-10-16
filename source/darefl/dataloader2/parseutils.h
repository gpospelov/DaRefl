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

#include <optional>
#include <string>
#include <vector>
#include <functional>

namespace DataLoader
{

//! Parses string for double values and returns result as a vector.
//! All non-numeric symbols are ingored.
std::vector<double> ParseSpaceSeparatedDoubles(const std::string& str);

//! Parses string for double values and stores result in a vector.
//! All non-numeric symbols are ingored.
void ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result);

//! Returns string after trimming whitespace surrounding.
//! Tabs and new line included.
std::string TrimWhitespace(const std::string& str);

//! Converts string to double value and returns it in the form of optional.
//! Strict: requires that string represents exactly one double and contains no other literals.
std::optional<double> StringToDouble(const std::string& str);

//! Loads ASCII file, returns it in the form of vector of strings.
std::vector<std::string> LoadASCIIFile(const std::string& file_name);

//! Split string on substring using given delimeter. Reproduces Python str.split() behavior.
std::vector<std::string> SplitString(const std::string& str, const std::string& delimeter);

//! Expands string representing line number pattern to inclusive pairs of line numbers.
//! "1" will be expanded to { {1, 1} }, "1, 3-5" will be expanded to { {1, 1}, {3, 5} }
//! Line numbers are counted starting from 1.
std::vector<std::pair<int, int>> ExpandLineNumberPattern(const std::string& pattern);

//! Removes repeating blanks for a string.
std::string RemoveRepeatedSpaces(std::string str);

//! Creates a callback to define if given line index satisfies line number pattern.
////! Line indices starts from 0, pattern starts from 1.
////! "1, 4-5"
//using accept_line_index_t = std::function<bool(int)>;
//accept_line_index_t CreateLineIndexValidator(const std::string& pattern);


} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
