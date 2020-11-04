// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <darefl/dataloader/dataloader_constants.h>
#include <darefl/dataloader/dataloader_utils.h>
#include <darefl/importdataview/graphimportdata.h>
#include <fstream>
#include <mvvm/utils/stringutils.h>

namespace
{

//! Returns true if given pair of values can represent range
bool isRepresentRange(const std::optional<int>& v0, const std::optional<int>& v1)
{
    if (v0.has_value() && v1.has_value())
        return v0.value() > 0 && v1.value() > 0 && v0.value() <= v1.value();
    return false;
}

//! Finds in vector of ColumnInfo all columns of given type and returns it as a new vector.
std::vector<DataLoader::ColumnInfo> columnsForType(const std::vector<DataLoader::ColumnInfo>& input,
                                                   const std::string& columnType)
{
    std::vector<DataLoader::ColumnInfo> result;
    std::copy_if(input.begin(), input.end(), std::back_inserter(result),
                 [columnType](auto x) { return x.type_name == columnType; });
    return result;
}

} // namespace

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

std::vector<std::pair<int, int>> DataLoader::ExpandLineNumberPattern(const std::string& pattern)
{
    std::vector<std::pair<int, int>> result;

    // splitting "1, 2-3" first on comma-separated tokens
    for (const auto& token : ModelView::Utils::SplitString(pattern, ",")) {
        auto parts = ModelView::Utils::SplitString(token, "-");
        // splitting on dash-separared tokens
        if (!parts.empty()) {
            // if no "-" is present, make from "1" a pair {1, 1}
            // if "-" is present, make from "1-2" a pair {1,2}
            auto conv0 = ModelView::Utils::StringToInteger(parts[0]);
            auto conv1 = parts.size() > 1 ? ModelView::Utils::StringToInteger(parts[1]) : conv0;
            if (isRepresentRange(conv0, conv1))
                result.push_back({conv0.value(), conv1.value()});
        }
    }

    return result;
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
DataLoader::CreateLinePrefixValidator(const std::string& prefix_to_exclude)
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
    if (separator.empty())
        throw std::runtime_error("Error, empty separator.");

    bool is_space_only_separator = separator.find_first_not_of(' ') == std::string::npos;
    auto result = [separator, is_space_only_separator](const std::string& line) {
        std::vector<std::string> values;
        std::string trimmed = ModelView::Utils::TrimWhitespace(line);
        if (is_space_only_separator)
            trimmed = ModelView::Utils::RemoveRepeatedSpaces(trimmed);
        return ModelView::Utils::SplitString(trimmed, separator);
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
            auto val1 = ModelView::Utils::StringToDouble(row[col1]);
            auto val2 = ModelView::Utils::StringToDouble(row[col2]);
            if (val1.has_value() && val2.has_value()) {
                vec1.push_back(val1.value());
                vec2.push_back(val2.value());
            }
        }
    }

    return std::make_pair(std::move(vec1), std::move(vec2));
}

std::vector<std::pair<DataLoader::ColumnInfo, DataLoader::ColumnInfo>>
DataLoader::CreateGraphInfoPairs(const std::vector<DataLoader::ColumnInfo>& column_info)
{
    std::vector<std::pair<DataLoader::ColumnInfo, DataLoader::ColumnInfo>> result;

    auto axis_columns = columnsForType(column_info, DataLoader::Constants::AxisType);
    auto intensity_columns = columnsForType(column_info, DataLoader::Constants::IntensityType);

    if (axis_columns.size() != 1)
        throw std::runtime_error("There must be exactly one column with AxisType selected.");

    for (const auto& intensity_info : intensity_columns)
        result.push_back(std::make_pair(axis_columns.back(), intensity_info));

    return result;
}

GraphImportData DataLoader::CreateData(const std::vector<std::vector<std::string>>& text_data,
                                       const DataLoader::ColumnInfo& axis,
                                       const DataLoader::ColumnInfo& intensity)
{
    GraphImportData result;

    auto [axis_values, intensity_values] =
        DataLoader::ExtractTwoColumns(text_data, axis.column, intensity.column);

    std::transform(intensity_values.begin(), intensity_values.end(), intensity_values.begin(),
                   [&intensity](auto x) { return x * intensity.multiplier; });

    result.bin_centers = axis_values;
    result.axis_units = axis.units;

    result.bin_values = intensity_values;
    result.signal_units = intensity.units;

    return result;
}
