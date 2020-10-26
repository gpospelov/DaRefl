// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader/defaultparser.h>
#include <darefl/dataloader/dataloader_utils.h>
#include <stdexcept>

using namespace DataLoader;

DefaultParser::DefaultParser(const ParserOptions& options)
{
    m_isSkipLineNumber = CreateLineNumberPatternValidator(options.m_skip_index_pattern);
    m_isValidLineContent = CreateLineContentBaseValidator(options.m_header_prefix);
    m_line_splitter = CreateSeparatorBasedSplitter(options.m_separator);
}

//! Parse data representing content of ASCII file.

void DefaultParser::process(const std::vector<std::string>& raw_data)
{
    m_rawData = raw_data;
    m_parsedData.clear();

    int index{0};
    for (const auto& line : m_rawData) {
        bool isValidLine = m_isValidLineContent(line) && !m_isSkipLineNumber(index + 1);

        if (isValidLine)
            m_parsedData.emplace(index, m_line_splitter(line));

        ++index;
    }
}

//! Returns total number of lines in raw data.

size_t DefaultParser::totalLineCount() const
{
    return m_rawData.size();
}

//! Returns total number of rows representing multi-column data.

size_t DefaultParser::dataRowCount() const
{
    return m_parsedData.size();
}

//! Returns a pair representing raw line and flag describing parsing results.

std::pair<std::string, ParserInterface::LineType> DefaultParser::getLine(size_t index) const
{
    if (index >= m_rawData.size())
        throw std::runtime_error("Error in DefaultParser: out of bounds.");

    if (m_parsedData.empty())
        return std::make_pair(m_rawData[index], ParserInterface::UNKNOWN);

    if (m_parsedData.find(index) == m_parsedData.end())
        return std::make_pair(m_rawData[index], ParserInterface::HEADER);
    else
        return std::make_pair(m_rawData[index], ParserInterface::DATA);
}

std::vector<std::string> DefaultParser::parseResults(size_t index) const
{
    auto it = m_parsedData.find(index);
    return it == m_parsedData.end() ? std::vector<std::string>() : it->second;
}

std::vector<std::vector<std::string>> DefaultParser::parseResults() const
{
    std::vector<std::vector<std::string>> result;
    for (size_t index = 0; index < totalLineCount(); ++index) {
        if (auto it = m_parsedData.find(index); it != m_parsedData.end())
            result.push_back(it->second);
    }

    return result;
}
