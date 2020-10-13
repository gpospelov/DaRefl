// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader2/parseutils.h>
#include <iostream>
#include <iterator>
#include <sstream>

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
