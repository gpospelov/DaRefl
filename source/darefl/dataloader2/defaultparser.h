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

#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/parserinterface.h>
#include <darefl/dataloader2/parseutils.h>
#include <functional>
#include <string>
#include <vector>
#include <map>

namespace DataLoader
{

//! Provides basic algorirthm for parsing multi-string data representing content
//! of multi-column ASCII file.
//! + Skips empty lines or lines matching the prefix.
//! + Skips lines matching given line number pattern.
//! + Parse data in columns of basing on given separator value.

class DefaultParser : public ParserInterface
{
public:
    DefaultParser(const ParserOptions& options);

    void process(const std::vector<std::string>& raw_data);

    size_t totalLineCount() const;

    size_t dataRowCount() const;

private:
    accept_line_number_t m_isSkipLineNumber;
    accept_line_t m_isValidLineContent;
    line_parser_t m_line_parser;
    std::vector<std::string> m_rawData;
    std::map<int, std::vector<std::string>> m_parsedData;
};

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_DEFAULTPARSER_H
