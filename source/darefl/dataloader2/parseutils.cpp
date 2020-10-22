// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <cctype>
#include <darefl/dataloader2/parseutils.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string_view>

namespace
{
//! Converts string to integer. Requires that string represents exactly one integer and
//! no extra symbols are defined. Empty spaces at the beginning and end of the string are still
//! allowed.
std::optional<int> StringToInt(const std::string& str)
{
    std::istringstream iss(DataLoader::TrimWhitespace(str));
    int value;
    iss >> value;
    return (!iss.fail() && iss.eof()) ? std::optional<int>(value) : std::optional<int>{};
}

//! Returns true if given pair of values can represent range
bool isRepresentRange(const std::optional<int>& v0, const std::optional<int>& v1)
{
    if (v0.has_value() && v1.has_value())
        return v0.value() > 0 && v1.value() > 0 && v0.value() <= v1.value();
    return false;
}

} // namespace

std::vector<double> DataLoader::ParseSpaceSeparatedDoubles(const std::string& str)
{
    std::vector<double> result;
    ParseSpaceSeparatedDoubles(str, result);
    return result;
}

void DataLoader::ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result)
{
    std::istringstream iss(str);
    iss.imbue(std::locale::classic());
    std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(),
              back_inserter(result));

    if (iss.fail()) {
        std::cout << "in fail state\n";
    }
}

std::string DataLoader::TrimWhitespace(const std::string& str)
{
    const char whitespace[]{" \t\n"};
    const size_t first = str.find_first_not_of(whitespace);
    if (std::string::npos == first)
        return {};
    const size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

std::optional<double> DataLoader::StringToDouble(const std::string& str)
{
    std::istringstream iss(DataLoader::TrimWhitespace(str));
    iss.imbue(std::locale::classic());
    double value;
    iss >> value;
    return (!iss.fail() && iss.eof()) ? std::optional<double>(value) : std::optional<double>{};
}

std::vector<std::string> DataLoader::LoadASCIIFile(const std::string& file_name)
{
    std::vector<std::string> result;

    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::ios_base::failure("Unable to open file '" + file_name + "'");
    for (std::string line; getline(file, line);)
        result.emplace_back(line);
    return result;
}

std::vector<std::string> DataLoader::SplitString(const std::string& str,
                                                 const std::string& delimeter)
{
    // splitting string following Python's str.split()
    if (delimeter.empty())
        throw std::runtime_error("Empty delimeter");
    if (str.empty())
        return {};

    std::vector<std::string> result;
    std::string_view view(str);
    size_t pos{0};

    while ((pos = view.find(delimeter)) != std::string::npos) {
        result.emplace_back(std::string(view.substr(0, pos)));
        view.remove_prefix(pos + delimeter.length());
    }
    result.emplace_back(std::string(view));
    return result;
}

std::vector<std::pair<int, int>> DataLoader::ExpandLineNumberPattern(const std::string& pattern)
{
    std::vector<std::pair<int, int>> result;

    // splitting "1, 2-3" first on comma-separated tokens
    for (const auto& token : SplitString(pattern, ",")) {
        auto parts = SplitString(token, "-");
        // splitting on dash-separared tokens
        if (!parts.empty()) {
            // if no "-" is present, make from "1" a pair {1, 1}
            // if "-" is present, make from "1-2" a pair {1,2}
            auto conv0 = StringToInt(parts[0]);
            auto conv1 = parts.size() > 1 ? StringToInt(parts[1]) : conv0;
            if (isRepresentRange(conv0, conv1))
                result.push_back({conv0.value(), conv1.value()});
        }
    }

    return result;
}

std::string DataLoader::RemoveRepeatedSpaces(std::string str)
{
    if (str.empty())
        return {};
    auto it = std::unique(str.begin(), str.end(),
                          [](auto x, auto y) { return x == y && std::isspace(x); });
    str.erase(it, str.end());
    return str;
}

DataLoader::accept_int_t DataLoader::CreateLineNumberPatternValidator(const std::string& pattern)
{
    std::vector<std::pair<int, int>> expanded_pattern =
        DataLoader::ExpandLineNumberPattern(pattern);
    auto result = [expanded_pattern](int line_number) {
        for (auto pair : expanded_pattern) {
            if (line_number >= pair.first && line_number <= pair.second)
                return true;
        }
        return false;
    };
    return result;
}

DataLoader::accept_string_t
DataLoader::CreateLineContentBaseValidator(const std::string& prefix_to_exclude)
{
    auto result = [prefix_to_exclude](const std::string& line) {
        // line contains spaces only
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos)
            return false;
        // line starts from pattern
        return line.find_first_of(prefix_to_exclude) == 0 ? false : true;
    };
    return result;
}

DataLoader::line_splitter_t DataLoader::CreateSeparatorBasedSplitter(const std::string& separator)
{
    // If no separator provided, use 'space'. Shall we throw exception instead?
    std::string sep = separator.empty() ? std::string(" ") : separator;

    bool is_space_only_separator = separator.find_first_not_of(' ') == std::string::npos;
    auto result = [sep, is_space_only_separator](const std::string& line) {
        std::vector<std::string> values;
        std::string trimmed = TrimWhitespace(line);
        if (is_space_only_separator)
            trimmed = RemoveRepeatedSpaces(trimmed);
        return SplitString(trimmed, sep);
    };
    return result;
}

std::string DataLoader::AddHtmlDivTag(const std::string& line)
{
    const std::string open_div = "<div>";
    const std::string close_div = "</div>";
    std::string result;
    return open_div + line + close_div;
}

std::string DataLoader::AddHtmlColorTag(const std::string& line, const std::string& color)
{
    const std::string open_tag = "<font color=\"" + color + "\">";
    const std::string close_tag = "</font>";
    std::string result;
    return open_tag + line + close_tag;
}

std::string DataLoader::AddHtmlBackgroundTag(const std::string& line, const std::string& color)
{
    const std::string open_tag = "<span style=\"background-color:" + color + "\">";
    const std::string close_tag = "</span>";
    std::string result;
    return open_tag + line + close_tag;
}

std::string DataLoader::AddHtmlColorTagToParts(const std::string& line,
                                               const std::vector<std::string>& parts,
                                               const std::string& color_parts,
                                               const std::string& color_rest)
{
    std::string result;
    std::string_view view(line);

    if (parts.empty())
        return AddHtmlDivTag(AddHtmlColorTag(line, color_rest));

    for (auto part : parts) {
        auto it = view.find_first_of(part);
        if (it > 0)
            result.append(AddHtmlBackgroundTag(std::string(view.substr(0, it)), color_rest));
        result.append(AddHtmlColorTag(part, color_parts));
        view.remove_prefix(it + part.size());
    }
    return AddHtmlDivTag(result);
}

std::pair<std::vector<double>, std::vector<double>>
DataLoader::ExtractTwoColumns(const std::vector<std::vector<std::string>>& text_data, size_t col1,
                              size_t col2)
{
    std::vector<double> vec1, vec2;
    for (const auto& row : text_data) {
        if (col1 < row.size() && col2 < row.size()) {
            auto val1 = StringToDouble(row[col1]);
            auto val2 = StringToDouble(row[col2]);
            if (val1.has_value() && val2.has_value()) {
                vec1.push_back(val1.value());
                vec2.push_back(val2.value());
            }
        }
    }

    return std::make_pair(std::move(vec1), std::move(vec2));
}
