// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDebug>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QListView>
#include <QSettings>
#include <QStringListModel>
#include <QVBoxLayout>
#include <darefl/dataloader2/importfilewidget_v2.h>
#include <mvvm/utils/fileutils.h>

namespace
{
const QString group_key = "dataloader";
const QString current_workdir_key = "currentworkdir";

const QString workdir_setting_name()
{
    return group_key + "/" + current_workdir_key;
}

} // namespace

ImportFileWidgetV2::ImportFileWidgetV2(QWidget* parent)
    : QWidget(parent), m_listView(new QListView), m_listModel(new QStringListModel)
{
    readSettings();

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_listView);

    m_listView->setModel(m_listModel);
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listView->setAlternatingRowColors(true);

    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &ImportFileWidgetV2::fileSelectionChanged);
}

ImportFileWidgetV2::~ImportFileWidgetV2()
{
    writeSettings();
}

//! Summons dialog for file selections, update list view with file names.

void ImportFileWidgetV2::onAddFilesRequest()
{
    QStringList file_names = QFileDialog::getOpenFileNames(
        this, "Select one or more files to load", m_currentWorkdir,
        "Text (*.txt *.csv);; Other (*.*)", nullptr, QFileDialog::DontUseNativeDialog);

    if (file_names.empty())
        return;

    updateCurrentWorkdir(file_names);
    addFileNamesToModel(file_names);

    emit fileNamesChanged();
}

//! Removes currently selected file

void ImportFileWidgetV2::onRemoveFileRequest() {}

//! Retuns the list of all file names imported by the user.

QStringList ImportFileWidgetV2::fileNames() const
{
    return m_listModel->stringList();
}

//! Retuns the list of currently selected file names.

QStringList ImportFileWidgetV2::selectedFileNames() const
{
    QStringList result;
    for (auto index : m_listView->selectionModel()->selectedIndexes())
        result.append(m_listModel->data(index).toString());
    return result;
}

//! Writes widget settings.

void ImportFileWidgetV2::writeSettings()
{
    QSettings settings;
    settings.setValue(workdir_setting_name(), m_currentWorkdir);
}

//! Loads widget settings.

void ImportFileWidgetV2::readSettings()
{
    QSettings settings;
    m_currentWorkdir = QDir::homePath();

    if (settings.contains(workdir_setting_name()))
        m_currentWorkdir = settings.value(workdir_setting_name()).toString();
}

//! Updates current working dir.

void ImportFileWidgetV2::updateCurrentWorkdir(const QStringList& file_names)
{
    auto file_name = file_names.back();
    auto parent_path = ModelView::Utils::parent_path(file_name.toStdString());
    m_currentWorkdir = QString::fromStdString(parent_path);
}

//! Adds given list of file names to the model.

void ImportFileWidgetV2::addFileNamesToModel(const QStringList& file_names)
{
    auto current_names = fileNames();
    QStringList updated_names = current_names + file_names;
    updated_names.removeDuplicates();
    m_listModel->setStringList(updated_names);

    emit fileNamesChanged();
}
