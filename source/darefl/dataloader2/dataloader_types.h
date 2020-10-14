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

struct ParseOptions {
    const std::string m_header_prefix = "#"; //!< prefix denoting header line
    const std::string m_separator = " ";     //!< column separator
//    const std::vector<int> m_indices_to_skip; //!< list of line indices to skip
    const std::string m_skip_index_pattern;  //!< pattern denoting line to skip (i.e. '0,10-12,42'),
                                             //!< starting from 0
};

struct ParseResults
{
    //!< array with results of column parsing
    std::vector<std::vector<std::string>> m_data;
};

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSEUTILS_H
