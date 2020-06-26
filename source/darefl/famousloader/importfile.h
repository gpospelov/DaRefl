// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTFILE_H
#define DAREFL_FAMOUSLOADER_IMPORTFILE_H

#include <string>
#include <vector>

namespace DataImportLogic
{

class ImportFile
{
public:
    ImportFile(std::string path_to_file);
    ~ImportFile() = default;

    const std::string& path() const;
    const std::vector<std::string>& thumbnail() const;
    const std::vector<std::string>& file() const;
    const std::string& line(int line_number) const;

private:
    void generateThumbnail();
    void loadFile();

private:
    std::string m_filepath;
    std::vector<std::string> m_thumbnail;
    std::vector<std::string> m_file;
    int m_thumbnail_length = 40;
};
} // namespace DataImportLogic

#endif  // DAREFL_FAMOUSLOADER_IMPORTFILE_H
