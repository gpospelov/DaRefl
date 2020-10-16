// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_PARSERINTERFACE_H
#define DAREFL_DATALOADER2_PARSERINTERFACE_H

#include <vector>
#include <functional>
#include <string>

namespace DataLoader
{

//! Interface for all classes capable of parsing ASCII data into multicolumn presentation.

class ParserInterface {
public:
    virtual ~ParserInterface() = default;

    using callback_rawdata_t = std::function<void(const std::string& line, bool status)>;
    using callback_parseddata_t = std::function<void(const std::string& line, bool status)>;


};

} // DataLoader


#endif // DAREFL_DATALOADER2_PARSERINTERFACE_H


