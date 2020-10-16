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

namespace DataLoader
{

//! Parser options to process multi column ASCII files.

struct ParserOptions {
    std::string m_header_prefix = "#"; //!< prefix denoting header line
    std::string m_separator = " ";     //!< column separator
    std::string m_skip_index_pattern;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
};

struct ParseResults
{
    //!< array with results of column parsing
    std::vector<std::vector<std::string>> m_data;
};

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
