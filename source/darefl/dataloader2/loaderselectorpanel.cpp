// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <algorithm>
#include <darefl/dataloader2/importfilewidget_v2.h>
#include <darefl/dataloader2/loaderselectorpanel.h>

LoaderSelectorPanel::LoaderSelectorPanel(QWidget* parent)
    : QWidget(parent), m_fileSelectorWidget(new ImportFileWidgetV2)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_fileSelectorWidget);

    connect(m_fileSelectorWidget, &ImportFileWidgetV2::fileNamesChanged,
            [this] { fileNamesChanged(); });
}

void LoaderSelectorPanel::onAddFilesRequest()
{
    m_fileSelectorWidget->onAddFilesRequest();
}

void LoaderSelectorPanel::onRemoveFileRequest()
{
    m_fileSelectorWidget->onRemoveFileRequest();
}

std::vector<std::string> LoaderSelectorPanel::fileNames() const
{
    std::vector<std::string> result;
    for (const auto& file_name : m_fileSelectorWidget->fileNames())
        result.push_back(file_name.toStdString());
    return result;
}
