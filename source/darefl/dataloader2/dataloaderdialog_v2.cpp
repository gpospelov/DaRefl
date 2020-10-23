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
#include <QKeyEvent>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/dataloader2/datahandler.h>
#include <darefl/dataloader2/dataloader_types.h>
#include <darefl/dataloader2/dataloaderdialog_v2.h>
#include <darefl/dataloader2/dataloadertoolbar.h>
#include <darefl/dataloader2/loaderpreviewpanel.h>
#include <darefl/dataloader2/loaderselectorpanel.h>
#include <darefl/dataloader2/parserinterface.h>
#include <darefl/dataloader2/parseutils.h>
#include <mvvm/utils/fileutils.h>

namespace
{
std::vector<std::string> toStringVector(const QStringList& container)
{
    std::vector<std::string> result;
    for (const auto& x : container)
        result.push_back(x.toStdString());
    return result;
}

QStringList toStringList(const std::vector<std::string>& container)
{
    QStringList result;
    for (const auto& x : container)
        result.push_back(QString::fromStdString(x));
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

std::vector<RealDataStruct> DataLoaderDialogV2::importedData() const
{
    return m_parsedData;
}

void DataLoaderDialogV2::setTargetCanvas(const std::vector<std::string>& canvas_names,
                                         int current_index)
{
    m_selectorPanel->setTargetCanvas(toStringList(canvas_names), current_index);
}

int DataLoaderDialogV2::targetCanvasIndex() const
{
    return m_selectorPanel->targetCanvasIndex();
}

void DataLoaderDialogV2::invokeFileSelectorDialog()
{
    m_selectorPanel->onAddFilesRequest();
}

void DataLoaderDialogV2::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        return;
    QDialog::keyPressEvent(event);
}

void DataLoaderDialogV2::accept()
{
    qDebug() << "processing all";
    process_all();
    qDebug() << "done";

    QDialog::accept();
    close();
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

    connect(m_selectorPanel, &LoaderSelectorPanel::fileSelectionChanged,
            [this]() { process_data(); });

    connect(m_selectorPanel, &LoaderSelectorPanel::parserPropertyChanged,
            [this]() { process_data(); });
}

//! Process currently selected file with given parser settings.

void DataLoaderDialogV2::process_data()
{
    auto selected_files = m_selectorPanel->selectedFileNames();
    if (selected_files.empty())
        return;

    auto data_to_parse = m_dataHandler->textData(selected_files.back().toStdString());

    auto parser = m_selectorPanel->createParser();
    parser->process(data_to_parse);

    m_previewPanel->showData(parser.get());
}

void DataLoaderDialogV2::process_all()
{
    m_parsedData.clear();

    auto parser = m_selectorPanel->createParser();
    for (const auto& name : m_selectorPanel->fileNames()) {
        auto data_to_parse = m_dataHandler->textData(name.toStdString());

        parser->process(data_to_parse);
        auto parsed_text = parser->parseResults();

        auto columns = m_previewPanel->columnInfo();
        for (auto [axis_info, intensity_info] : DataLoader::CreateGraphInfoPairs(columns)) {
            auto data = DataLoader::CreateData(parsed_text, axis_info, intensity_info);
            data.name = ModelView::Utils::base_name(name.toStdString());
            m_parsedData.emplace_back(data);
        }
    }
}
