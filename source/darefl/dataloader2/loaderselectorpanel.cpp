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
#include <darefl/dataloader2/parserpropertywidget.h>
#include <darefl/dataloader2/defaultparser.h>

LoaderSelectorPanel::LoaderSelectorPanel(QWidget* parent)
    : QWidget(parent), m_fileSelectorWidget(new ImportFileWidgetV2),
      m_propertyWidget(new ParserPropertyWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_fileSelectorWidget);
    layout->addWidget(m_propertyWidget);

    init_connections();
}

LoaderSelectorPanel::~LoaderSelectorPanel() = default;

std::unique_ptr<DataLoader::DefaultParser> LoaderSelectorPanel::createParser() const
{
    return m_propertyWidget->createParser();
}

void LoaderSelectorPanel::onAddFilesRequest()
{
    m_fileSelectorWidget->onAddFilesRequest();
}

void LoaderSelectorPanel::onRemoveFileRequest()
{
    m_fileSelectorWidget->onRemoveFileRequest();
}

void LoaderSelectorPanel::init_connections()
{
    auto on_file_names_changed = [this]() { fileNamesChanged(m_fileSelectorWidget->fileNames()); };
    connect(m_fileSelectorWidget, &ImportFileWidgetV2::fileNamesChanged, on_file_names_changed);

    auto on_selection_changed = [this]() {
        fileSelectionChanged(m_fileSelectorWidget->selectedFileNames());
    };
    connect(m_fileSelectorWidget, &ImportFileWidgetV2::fileSelectionChanged, on_selection_changed);

    connect(m_propertyWidget, &ParserPropertyWidget::parserPropertyChanged, this,
            &LoaderSelectorPanel::parserPropertyChanged);
}
