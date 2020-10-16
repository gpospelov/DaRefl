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
    m_isValidLineNumber = CreateLineNumberPatternValidator(options.m_skip_index_pattern);
    m_isValidLineContent = CreateLineContentBaseValidator(options.m_header_prefix);
    m_line_parser = CreateSeparatorBasedLineParser(options.m_separator);
}

void DefaultParser::setRawData(const std::vector<std::string>& raw_data)
{
    m_rawData = raw_data;
}

//! Returns total number of lines in a vector.

size_t DefaultParser::totalLineCount() const
{
    return m_rawData.size();
}

//! Returns number of data rows, i.e. a number of successfully parsed lines.

size_t DefaultParser::dataRowCount() const
{
    return m_parsedData.size();
}

#include <iostream>
void DefaultParser::parse()
{
    m_parsedData.clear();

    int index{0};
    for (const auto& line : m_rawData) {
//        bool isValidLine = m_isValidLineContent(line) && m_isValidLineNumber(index + 1);
        bool isValidLine = m_isValidLineContent(line);

        if (isValidLine)
        std::cout << "xxx" << line << m_line_parser(line).size() << std::endl;
            m_parsedData.emplace_back(m_line_parser(line));

        ++index;
    }
}
