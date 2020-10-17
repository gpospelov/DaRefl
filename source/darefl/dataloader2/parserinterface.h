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

#include <functional>
#include <string>
#include <vector>

namespace DataLoader
{

//! Interface for all classes capable of parsing ASCII data into multicolumn presentation.

class ParserInterface
{
public:
    virtual ~ParserInterface() = default;

    //! Parse data representing content of ASCII file.
    virtual void process(const std::vector<std::string>& raw_data) = 0;

    //! Returns total number of lines in raw data.
    virtual size_t totalLineCount() const = 0;

    //! Returns total number of rows representing multi-column data.
    virtual size_t dataRowCount() const = 0;
};

} // namespace DataLoader

#endif // DAREFL_DATALOADER2_PARSERINTERFACE_H
