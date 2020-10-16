// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_DEFAULTPARSER_H
#define DAREFL_DATALOADER2_DEFAULTPARSER_H

#include <string>
#include <vector>
#include <functional>
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/parseutils.h>

namespace DataLoader
{

//! Provides basic algorirthm for parsing multi-string data representing content
//! of multi-column ASCII file.

class DefaultParser {
public:
    DefaultParser(const ParserOptions& options);

    void setRawData(const std::vector<std::string>& raw_data);

    size_t totalLineCount() const;

    size_t dataRowCount() const;

    void parse();

private:
    accept_line_number_t m_isValidLineNumber;
    accept_line_t m_isValidLineContent;
    std::vector<std::string> m_rawData;
    std::vector<std::vector<std::string>> m_parsedData;
};


} // namespace DataLoader

#endif // DAREFL_DATALOADER2_DEFAULTPARSER_H
