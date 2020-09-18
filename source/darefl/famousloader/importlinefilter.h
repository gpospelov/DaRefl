// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTLINEFILTER_H
#define DAREFL_FAMOUSLOADER_IMPORTLINEFILTER_H

#include <darefl/famousloader/importdatastructure.h>
#include <darefl/famousloader/importoutput.h>

#include <map>
#include <string>
#include <vector>

namespace DataImportLogic
{

//! This is the class holding a text region
class LineFilter
{
public:
    LineFilter(std::string name);
    ~LineFilter() = default;

    //! Public access
    void setSeparators(std::map<std::string, char>* separators);
    std::vector<std::string> separatorNames() const;
    void processColors(std::vector<std::string>& color_vec) const;
    void processSeparator(std::vector<char>& separator_vec) const;
    void processType(std::vector<std::string>& type_vec) const;
    void processIgnore(std::vector<std::vector<std::string>>& ignore_vec) const;

    //! Getters
    std::string name() const;
    bool active() const;
    std::string type() const;
    std::string separator() const;
    std::string color() const;
    std::vector<std::string> ignoreStrings() const;
    std::string ignoreString() const;
    std::vector<std::vector<int>> ignoreLines() const;
    int start() const;
    int end() const;

    //! Setters
    void setName(std::string);
    void setActive(bool active);
    void setType(std::string type_string);
    void setSeparator(std::string separator_name);
    void setColor(std::string color_string);
    void setIgnoreStrings(std::vector<std::string>& ignore_strings);
    void setIgnoreString(std::string ignore_string);
    void setIgnoreLines(std::vector<std::vector<int>>);
    void setStart(int start_line);
    void setEnd(int end_line);

private:
    bool lineIgnored(int line_num) const;

private:
    std::string m_name;
    std::string m_separator_str;
    std::string m_type_string;
    std::string m_color;

    std::vector<std::string> m_ignore_strings;
    std::vector<std::vector<int>> m_ignore_lines;

    bool m_active;
    char m_separator = ' ';

    int m_start_line;
    int m_end_line;

    std::map<std::string, char>* m_separators{nullptr};
};

} // namespace DataImportLogic

#endif // DAREFL_FAMOUSLOADER_IMPORTLINEFILTER_H
