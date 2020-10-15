// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDebug>
#include <QDialogButtonBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <darefl/dataloader2/datahandler.h>
#include <darefl/dataloader2/dataloaderdialog_v2.h>
#include <darefl/dataloader2/dataloadertoolbar.h>
#include <darefl/dataloader2/loaderpreviewpanel.h>
#include <darefl/dataloader2/loaderselectorpanel.h>

namespace
{
std::vector<std::string> toStringVector(const QStringList& container)
{
    std::vector<std::string> result;
    for (const auto& x : container)
        result.push_back(x.toStdString());
    return result;
}
} // namespace

DataLoaderDialogV2::DataLoaderDialogV2(QWidget* parent)
    : QDialog(parent), m_toolBar(new DataLoaderToolBar), m_selectorPanel(new LoaderSelectorPanel),
      m_previewPanel(new LoaderPreviewPanel), m_splitter(new QSplitter),
      m_dataHandler(std::make_unique<DataHandler>())
{
    m_splitter->addWidget(m_selectorPanel);
    m_splitter->addWidget(m_previewPanel);

    auto button_box = new QDialogButtonBox;
    auto button = button_box->addButton("Import data", QDialogButtonBox::AcceptRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    button = button_box->addButton("Cancel", QDialogButtonBox::RejectRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    connect(button_box, &QDialogButtonBox::accepted, this, &DataLoaderDialogV2::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &DataLoaderDialogV2::reject);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);
    layout->addWidget(button_box);

    init_connections();
    setWindowTitle("Data import dialog");
}

void DataLoaderDialogV2::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        return;
    QDialog::keyPressEvent(event);
}

DataLoaderDialogV2::~DataLoaderDialogV2() = default;

//! Init interconnections of all widgets.

void DataLoaderDialogV2::init_connections()
{
    // connect toolbar and LoaderSelectorPanel
    connect(m_toolBar, &DataLoaderToolBar::addFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onAddFilesRequest);
    connect(m_toolBar, &DataLoaderToolBar::removeFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onRemoveFileRequest);

    // connect LoaderSelectorPanel with DataHandler
    auto on_file_list_changed = [this](const auto& container) {
        m_dataHandler->updateRawData(toStringVector(container));
    };
    connect(m_selectorPanel, &LoaderSelectorPanel::fileNamesChanged, on_file_list_changed);

    auto on_selection_changed = [this](const auto& container) {
        qDebug() << "selected" << container;
        if (!container.empty())
            m_previewPanel->setTextData(m_dataHandler->textData(container.back().toStdString()));
    };
    connect(m_selectorPanel, &LoaderSelectorPanel::fileSelectionChanged, on_selection_changed);
}
