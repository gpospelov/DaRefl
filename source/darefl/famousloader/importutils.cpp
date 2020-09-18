// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/famousloader/importutils.h>

#include <functional>
#include <iostream>
#include <sstream>

namespace DataImportUtils
{

//! Standard function to handle spinting
std::vector<std::string> split(const std::string& s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

//! Cleans the vector of strings provided by removing empty parts
void clean(std::vector<std::string>& input)
{
    std::vector<std::string>::iterator i = input.begin();
    while (i != input.end()) {
        if (*i == "") {
            i = input.erase(i);
        } else {
            ++i;
        }
    }
}

//! Erase All substrings
void eraseSubStrings(std::string& main_string, const std::vector<std::string>& string_vector)
{
    std::for_each(string_vector.begin(), string_vector.end(),
                  std::bind(eraseAllSubString, std::ref(main_string), std::placeholders::_1));
}

//! Erase All occurences of substring
void eraseAllSubString(std::string& main_string, const std::string& to_erase)
{
    if (to_erase == "")
        return;

    // Search for the substring in string in a loop untill nothing is found
    for (std::string::size_type i = main_string.find(to_erase); i != std::string::npos;
         i = main_string.find(to_erase)) {
        // If found then erase it from string
        main_string.erase(i, to_erase.length());
    }
}

//! Tranform text into vector of ints
std::vector<std::vector<int>> getRangesFromString(const std::string text_input)
{

    std::vector<std::vector<int>> output;
    std::vector<std::string> split_input = split(text_input, ',');

    for (int i = 0; i < split_input.size(); ++i) {
        std::vector<int> temp;
        std::vector<std::string> split_sub_input = split(split_input[i], '-');

        for (int j = 0; j < split_sub_input.size(); ++j) {
            try {
                temp.push_back(std::stoi(split_sub_input[j]));
            } catch (...) {
                temp.push_back(0);
            }
        }

        output.push_back(temp);
    }
    return output;
}

} // namespace DataImportUtils
