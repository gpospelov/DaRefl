// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/dataloader/dataimportdialog.h>

#include <darefl/dataloader/importfilewidget.h>
#include <darefl/dataloader/importfilterwidget.h>
#include <darefl/dataloader/importtableview.h>
#include <darefl/dataloader/importtextview.h>
#include <darefl/dataloader/importutils.h>

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QSplitter>
#include <QString>
#include <QVBoxLayout>

namespace DataImportGui
{

//! This is the constructor
DataLoaderDialog::DataLoaderDialog(QWidget* parent) : QDialog(parent)
{
    // Init the main import logic
    m_dataImportLogic =
        std::unique_ptr<DataImportLogic::ImportLogic>(new DataImportLogic::ImportLogic());

    // The placeholders
    auto h_splitter = new QSplitter(this);
    auto v_splitter = new QSplitter(Qt::Vertical, h_splitter);
    h_splitter->setChildrenCollapsible(false);
    v_splitter->setChildrenCollapsible(false);

    auto file_list_space = new QGroupBox("Selected Files:", v_splitter);
    auto parameter_space = new QGroupBox("Text Selection rules:", v_splitter);
    m_selectionSpace = new QTabWidget(v_splitter);

    // The dialog buttons
    m_targetSelect = new QComboBox(this);
    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    dynamic_cast<QBoxLayout*>(button_box->layout())
        ->insertWidget(0, new QLabel("Select the target canvas ", this));
    dynamic_cast<QBoxLayout*>(button_box->layout())->insertWidget(1, m_targetSelect);
    connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));

    // Set up the individual elements
    setUpFileListSpace(file_list_space);
    setUpParameterSpace(parameter_space);
    setUpSelectionSpace(m_selectionSpace);

    // Manage the layout
    v_splitter->addWidget(file_list_space);
    v_splitter->addWidget(parameter_space);
    h_splitter->addWidget(v_splitter);
    h_splitter->addWidget(m_selectionSpace);

    auto v_layout = new QVBoxLayout(this);
    v_layout->addWidget(h_splitter);
    v_layout->addWidget(button_box);

    v_splitter->setStretchFactor(0, 0);
    v_splitter->setStretchFactor(1, 1);
    h_splitter->setStretchFactor(0, 0);
    h_splitter->setStretchFactor(1, 1);

    readSettings();
    setWindowTitle("Data import dialog");
}

//! Set the targets of the import withe a vector of string and data string (identifier)
void DataLoaderDialog::setTargets(std::vector<std::pair<std::string, std::string>> target_name_data,
                                  std::string current_target)
{
    m_targetSelect->addItem("New canvas ...", QString::fromStdString(""));
    for (auto target_name : target_name_data) {
        m_targetSelect->addItem(QString::fromStdString(target_name.first),
                                QString::fromStdString(target_name.second));
    }
    m_targetSelect->setCurrentText(QString::fromStdString(current_target));
}

//! Build and set out the final result
DataImportLogic::ImportOutput DataLoaderDialog::result()
{
    auto result = m_dataImportLogic->getFinalOutput();
    result.setTarget(m_targetSelect->currentData().value<QString>().toStdString());
    return result;
}

//! Trigger the file dialog manually
void DataLoaderDialog::triggerFileDialog()
{
    m_importFileList->addFiles();
}

//! Helper function to set up the file list area
void DataLoaderDialog::setUpFileListSpace(QGroupBox* conainer)
{

    auto layout = new QVBoxLayout(conainer);
    m_importFileList = new ImportFileWidget(conainer);
    layout->addWidget(m_importFileList);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    conainer->setMinimumHeight(m_importFileList->minimumHeight());

    connect(m_importFileList, &ImportFileWidget::filesChanged,
            [this](const std::vector<std::string>& files) {
                m_dataImportLogic.get()->setFiles(files);
            });

    connect(m_importFileList, SIGNAL(selectionChanged()), this, SLOT(selectedFileChanged()));
}

//! Helper function to set up the parameter area
void DataLoaderDialog::setUpParameterSpace(QGroupBox* conainer)
{

    auto layout = new QVBoxLayout(conainer);
    m_parameterDialog = new ImportFilterWidget(m_dataImportLogic.get(), conainer);
    layout->addWidget(m_parameterDialog);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    conainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    connect(m_parameterDialog, SIGNAL(parameterChanged()), this, SLOT(selectedFileChanged()));
}

//! Helper function to set up the selection area
void DataLoaderDialog::setUpSelectionSpace(QTabWidget* tab_widget)
{
    auto first_tab = new QWidget(tab_widget);
    auto first_layout = new QVBoxLayout(first_tab);
    m_textView = new ImportTextView(first_tab);
    first_layout->addWidget(m_textView);

    auto second_tab = new QWidget(tab_widget);
    auto second_layout = new QVBoxLayout(second_tab);
    m_tableView = new ImportTableView(second_tab);
    m_tableView->model()->setDataStructure(m_dataImportLogic->dataStructure());
    second_layout->addWidget(m_tableView);

    tab_widget->addTab(first_tab, "Text view");
    tab_widget->addTab(second_tab, "Table view");

    connect(tab_widget, &QTabWidget::currentChanged, this, &DataLoaderDialog::selectedFileChanged);
}

//! This function will manage the chnage of file selection
void DataLoaderDialog::selectedFileChanged()
{
    int file_num = m_importFileList->currentSelection();
    if (file_num < 0) {
        m_textView->setHtml("");
        m_tableView->model()->refreshFromDataStructure();
    } else {
        if (m_selectionSpace->currentIndex() == 0) {
            m_textView->setHtml(QString::fromStdString(m_dataImportLogic->getPreview(file_num)));
        } else if (m_selectionSpace->currentIndex() == 1) {
            m_dataImportLogic->updateData(file_num);
            m_tableView->model()->refreshFromDataStructure();
        }
    }
}

//! Write the QSettings
void DataLoaderDialog::writeSettings()
{
    QSettings settings("quickrefl", "ImportDialog");

    settings.beginGroup("Geometry");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    m_importFileList->writeSettings();
    m_parameterDialog->writeSettings();
    writeImportLogicSettings();
}

//! read the Qsettings
void DataLoaderDialog::readSettings()
{
    QSettings settings("quickrefl", "ImportDialog");

    settings.beginGroup("Geometry");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    m_importFileList->readSettings();
    m_parameterDialog->readSettings();
    readImportLogicSettings();
}

//! Write the QSettings related to the import logic
void DataLoaderDialog::writeImportLogicSettings()
{
    QSettings settings;

    settings.beginGroup("ColumnHistory");
    settings.remove("");
    settings.endGroup();

    auto history = m_dataImportLogic->dataStructure()->columnHistory();
    settings.beginGroup("ColumnHistory");
    for (int i = 0; i < history.size(); ++i) {
        settings.beginGroup(QString::number(i));
        settings.setValue("Name", QString::fromStdString(history.at(i).at(0)));
        settings.setValue("Type", QString::fromStdString(history.at(i).at(1)));
        settings.setValue("Unit", QString::fromStdString(history.at(i).at(2)));
        settings.setValue("Multiplier", QString::fromStdString(history.at(i).at(3)));
        settings.endGroup();
    }
    settings.endGroup();
}

//! read the Qsettings for the import logic
void DataLoaderDialog::readImportLogicSettings()
{
    QSettings settings;
    DataImportUtils::string_data history;
    settings.beginGroup("ColumnHistory");
    if (settings.childGroups().count() != 0) {
        for (auto group_name : settings.childGroups()) {
            settings.beginGroup(group_name);
            history.push_back(std::vector<std::string>{
                settings.value("Name", "").toString().toStdString(),
                settings.value("Type", "").toString().toStdString(),
                settings.value("Unit", "").toString().toStdString(),
                settings.value("Multiplier", "").toString().toStdString(),
            });
            settings.endGroup();
        }
    }
    settings.endGroup();

    m_dataImportLogic->dataStructure()->setColumnHistory(history);
}

void DataLoaderDialog::accept()
{
    QDialog::accept();
    writeSettings();
    close();
}

} // End of namespace DataImportGui
