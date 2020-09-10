// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_DATAIMPORTDIALOG_H
#define DAREFL_FAMOUSLOADER_DATAIMPORTDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QSettings>
#include <QTabWidget>
#include <darefl/famousloader/importlogic.h>

#include <memory>
#include <string>

namespace DataImportLogic
{
class ImportOutput;
}

namespace DataImportGui
{

class ImportFileWidget;
class ImportFilterWidget;
class ImportTextView;
class ImportTableView;
class ImportOutput;

//! This is the main dialog for the data loader
class DataLoaderDialog : public QDialog
{
    Q_OBJECT

public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog() = default;

    void setTargets(std::vector<std::pair<std::string, std::string>> target_name_data,
                    std::string current_target);
    DataImportLogic::ImportOutput result();

    void triggerFileDialog();

private:
    void setUpFileListSpace(QGroupBox* conainer);
    void setUpParameterSpace(QGroupBox* conainer);
    void setUpSelectionSpace(QTabWidget* tab_widget);

    void readSettings();
    void writeSettings();

    void readImportLogicSettings();
    void writeImportLogicSettings();

private slots:
    void selectedFileChanged();

protected:
    void accept() override;

private:
    ImportFileWidget* p_import_file_list{nullptr};
    ImportFilterWidget* p_parameter_dialog{nullptr};
    ImportTextView* p_text_view{nullptr};
    ImportTableView* p_table_view{nullptr};
    std::unique_ptr<DataImportLogic::ImportLogic> p_data_import_logic;
    QTabWidget* p_selection_space{nullptr};
    QComboBox* p_target_select{nullptr};
};

} // End of namespace DataImportGui

#endif // DAREFL_FAMOUSLOADER_DATAIMPORTDIALOG_H
