// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_DATALOADER_TYPES_H
#define DAREFL_DATALOADER2_DATALOADER_TYPES_H

#include <string>
#include <vector>
#include <functional>

namespace DataLoader
{

//! Parser options to process multi column ASCII files.

struct ParserOptions {
    std::string m_header_prefix = "#"; //!< prefix denoting header line
    std::string m_separator = " ";     //!< column separator
    std::string m_skip_index_pattern;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
};

struct LineParseResults
{
    std::string m_orig_string;
    std::vector<std::string> m_parts;
};

//! Function to define if given index satisfies criteria.
using accept_int_t = std::function<bool(int)>;

//! Function to define if given string should be accepted for further consideration.
using accept_string_t = std::function<bool(const std::string& line)>;

//! Function to define line splitter according to some criteria.
using line_splitter_t = std::function<std::vector<std::string>(const std::string& line)>;


} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
