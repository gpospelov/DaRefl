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

std::optional<double> DataLoader::StringToDouble(const std::string& str)
{
    std::istringstream iss(str);
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
    size_t pos = view.find(delimeter);

    while (pos != std::string::npos) {
        result.emplace_back(std::string(view.substr(0, pos)));
        view.remove_prefix(pos + delimeter.length());
        pos = view.find(delimeter);
    }

    result.emplace_back(std::string(view));

    return result;
}

std::vector<std::pair<int, int>> DataLoader::ExpandLineNumberPattern(const std::string& pattern)
{
    std::vector<std::pair<int, int>> result;
    //    std::vector<std::string> tokens;
    //    std::string token;

    //    std::istringstream istr(pattern);
    //    while (getline(istr, token, ','))
    //        tokens.push_back(token);

    //    for (const auto& x : tokens) {
    //        if (x.find_first_of('-') == std::string::npos) {
    //            int index = std::stoi(x) - 1;
    //            result.push_back({index, index});
    //        } else {

    //        }
    //    }

    return result;
}
