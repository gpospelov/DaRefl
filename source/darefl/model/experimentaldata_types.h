// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_EXPERIMENTALDATA_TYPES_H
#define DAREFL_MODEL_EXPERIMENTALDATA_TYPES_H

#include <string>
#include <vector>

//! Convenience data transfer structure

struct RealDataStruct {
    std::string graph_description;

    std::vector<double> bin_centers;
    std::string axis_name;
    std::string axis_unit;

    std::vector<double> bin_values;
    std::string data_name;
    std::string data_unit;
};

#endif // DAREFL_MODEL_EXPERIMENTALDATA_TYPES_H
