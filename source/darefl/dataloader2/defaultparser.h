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

    void process(const std::vector<std::string>& raw_data) override;

    size_t totalLineCount() const override;

    size_t dataRowCount() const override;

    std::pair<std::string, LineType> getLine(size_t index) const override;

    std::vector<std::string> parseResults(size_t index) const override;

    std::vector<std::vector<std::string>> parseResults() const override;

private:
    accept_int_t m_isSkipLineNumber;
    accept_string_t m_isValidLineContent;
    line_splitter_t m_line_splitter;
    std::vector<std::string> m_rawData;
    //!< correspondance of parsed data to original line index
    std::map<size_t, std::vector<std::string>> m_parsedData;
};

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_DEFAULTPARSER_H