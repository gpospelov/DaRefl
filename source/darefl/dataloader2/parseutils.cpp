// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/parseutils.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string_view>

namespace
{
//! Converts string to integer. Requires that string represents exactly one integer and
//! no extra symbols are defined.
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

    auto tokens = SplitString(pattern, ",");

    for (const auto& token : tokens) {
        auto parts = SplitString(token, "-");
        if (!parts.empty()) {
            auto conv0 = StringToInt(parts[0]);
            auto conv1 = parts.size() > 1 ? StringToInt(parts[1]) : conv0;
            if (isRepresentRange(conv0, conv1))
                result.push_back({conv0.value() - 1, conv1.value() - 1});
        }
    }

    return result;
}
