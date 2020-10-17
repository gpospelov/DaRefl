// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/defaultparser.h>

using namespace DataLoader;

DefaultParser::DefaultParser(const ParserOptions& options)
{
    m_isSkipLineNumber = CreateLineNumberPatternValidator(options.m_skip_index_pattern);
    m_isValidLineContent = CreateLineContentBaseValidator(options.m_header_prefix);
    m_line_parser = CreateSeparatorBasedLineParser(options.m_separator);
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
            m_parsedData.emplace(index, m_line_parser(line));

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
