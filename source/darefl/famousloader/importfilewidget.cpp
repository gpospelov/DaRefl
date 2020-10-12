// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/famousloader/importfilewidget.h>
#include <darefl/mainwindow/styleutils.h>

#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QItemSelectionModel>
#include <QListView>
#include <QSettings>
#include <QSizePolicy>
#include <QStringListModel>
#include <QStyle>
#include <QToolButton>

namespace DataImportGui
{

//! This is the constructor
ImportFileWidget::ImportFileWidget(QWidget* parent) : QWidget(parent)
{
    createWidgets();
}

//! Create all the widget elements
void ImportFileWidget::createWidgets()
{
    auto main_layout = new QHBoxLayout(this);
    auto side_layout = new QVBoxLayout();

    // Set up the list
    m_listView = new QListView(this);
    m_listModel = new QStringListModel(this);
    m_listView->setModel(m_listModel);
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set up the buttons
    auto add_button = new QToolButton(this);
    add_button->setObjectName("add_file_button");
    add_button->setIcon(QIcon(":/icons/file-plus.svg"));
    add_button->setToolTip("Add further files to the import procedure.");

    auto reset_button = new QToolButton(this);
    add_button->setObjectName("reset_file_button");
    reset_button->setIcon(QIcon(":/icons/file-remove.svg"));
    reset_button->setToolTip("Remove all currently selected files.");

    // Build the layout
    main_layout->addWidget(m_listView);
    side_layout->addWidget(add_button);
    side_layout->addWidget(reset_button);
    side_layout->addStretch();
    main_layout->addLayout(side_layout);

    // Connect the buttons
    connect(add_button, &QToolButton::clicked, this, &ImportFileWidget::addFiles);
    connect(reset_button, &QToolButton::clicked, this, &ImportFileWidget::resetFiles);
    connect(m_listView->selectionModel(), &QItemSelectionModel::currentChanged,
            [=](QModelIndex, QModelIndex) { emit selectionChanged(); });
}

//! Get the current selection
int ImportFileWidget::currentSelection() const
{
    return m_listView->currentIndex().row();
}

//! Read the settings froma QSetting structure
void ImportFileWidget::readSettings()
{
    QSettings settings;

    settings.beginGroup("Files");
    m_defaultPath = settings.value("last_path", ".").toString();
    settings.endGroup();
}

//! Write the settings from a QSetting structure
void ImportFileWidget::writeSettings()
{
    QSettings settings;

    settings.beginGroup("Files");
    settings.setValue("last_path", m_defaultPath);
    settings.endGroup();
}

//! This is the method called by the add file button
void ImportFileWidget::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select one or more files to load",
                                                      m_defaultPath, "Text (*.txt);; CSV (*.csv)",
                                                      nullptr, QFileDialog::DontUseNativeDialog);
    if (files.count() > 0)
        m_defaultPath = QFileInfo(files[0]).absoluteDir().absolutePath();

    // Save the current string
    QString current_input;
    if (m_listModel->rowCount() != 0
        && m_listView->selectionModel()->selectedIndexes().count() != 0) {
        current_input =
            m_listModel->data(m_listView->selectionModel()->selectedIndexes()[0]).value<QString>();
    }

    // Refresh
    files = m_listModel->stringList() + files;
    files.removeDuplicates();
    m_listModel->setStringList(files);
    emit filesChanged(currentFiles());

    // Set back the initial string is present
    if (m_listModel->rowCount() != 0) {
        auto to_select = m_listModel->index(0, 0);
        for (int i = 0; i < m_listModel->rowCount(); ++i) {
            if (current_input.toStdString()
                == m_listModel->data(m_listModel->index(i, 0)).value<QString>().toStdString()) {
                to_select = m_listModel->index(i, 0);
                break;
            }
        }
        m_listView->setCurrentIndex(to_select);
    }
}

//! This is the method called by the reset file button
void ImportFileWidget::resetFiles()
{
    m_listModel->setStringList(QStringList());
    emit filesChanged(currentFiles());
}

//! Return the string list formated as a vector of strings
std::vector<std::string> ImportFileWidget::currentFiles() const
{
    std::vector<std::string> string_vector;
    foreach (QString str, m_listModel->stringList()) {
        string_vector.push_back(str.toStdString());
    }
    return string_vector;
}

} // End of namespace DataImportGui
