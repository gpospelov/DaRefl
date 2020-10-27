// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_PARSERINTERFACE_H
#define DAREFL_DATALOADER_PARSERINTERFACE_H

#include <string>
#include <vector>

namespace DataLoader
{

//! Interface for all classes capable of parsing ASCII data into multicolumn presentation.

class ParserInterface
{
public:
    //! Defines type of line
    enum LineType { UNKNOWN, HEADER, DATA };

    virtual ~ParserInterface() = default;

    //! Parse data representing content of ASCII file.
    virtual void process(const std::vector<std::string>& raw_data) = 0;

    //! Returns total number of lines in raw data.
    virtual size_t totalLineCount() const = 0;

    //! Returns a pair representing raw line and flag describing parsing results.
    virtual std::pair<std::string, LineType> getLine(size_t index) const = 0;

    virtual  std::vector<std::string> parseResults(size_t index) const = 0;

    virtual  std::vector<std::vector<std::string>> parseResults() const = 0;

};

} // namespace DataLoader

#endif // DAREFL_DATALOADER_PARSERINTERFACE_H
