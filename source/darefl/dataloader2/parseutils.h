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

#include <vector>
#include <string>
#include <optional>

namespace DataLoader
{

//! Parses string for double values and returns result as a vector.
//! All non-numeric symbols are ingored.
std::vector<double> ParseSpaceSeparatedDoubles(const std::string& str);

//! Parses string for double values and stores result in a vector.
//! All non-numeric symbols are ingored.
void ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result);

//! Converts string to double value and returns it in the form of optional.
//! Strict: requires that string represents exactly one double and contains no other literals.
std::optional<double> StringToDouble(const std::string& str);

//! Loads ASCII file, returns it in the form of vector of strings.
std::vector<std::string> LoadASCIIFile(const std::string& file_name);

}

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
