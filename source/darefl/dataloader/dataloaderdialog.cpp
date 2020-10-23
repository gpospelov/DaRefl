// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QDialogButtonBox>
#include <QKeyEvent>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/core/app_constants.h>
#include <darefl/dataloader/datahandler.h>
#include <darefl/dataloader/dataloader_types.h>
#include <darefl/dataloader/dataloaderdialog.h>
#include <darefl/dataloader/dataloadertoolbar.h>
#include <darefl/dataloader/loaderpreviewpanel.h>
#include <darefl/dataloader/loaderselectorpanel.h>
#include <darefl/dataloader/parserinterface.h>
#include <darefl/dataloader/parseutils.h>
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

const QString dialogsize_key = "dialogsize";
const QString splittersize_key = "splittersize";

const QString dialogsize_setting_name()
{
    return Constants::DataLoaderGroupKey + "/" + dialogsize_key;
}

const QString splittersize_setting_name()
{
    return Constants::DataLoaderGroupKey + "/" + splittersize_key;
}

} // namespace

DataLoaderDialog::DataLoaderDialog(QWidget* parent)
    : QDialog(parent), m_toolBar(new DataLoaderToolBar), m_selectorPanel(new LoaderSelectorPanel),
      m_previewPanel(new LoaderPreviewPanel), m_splitter(new QSplitter),
      m_dataHandler(std::make_unique<DataHandler>())
{
    m_splitter->setChildrenCollapsible(false);
    m_splitter->addWidget(m_selectorPanel);
    m_splitter->addWidget(m_previewPanel);

    auto button_box = new QDialogButtonBox;
    auto button = button_box->addButton("Import data", QDialogButtonBox::AcceptRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    button = button_box->addButton("Cancel", QDialogButtonBox::RejectRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    connect(button_box, &QDialogButtonBox::accepted, this, &DataLoaderDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &DataLoaderDialog::reject);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);
    layout->addWidget(button_box);

    init_connections();
    setWindowTitle("Data import dialog");

    readSettings();
}

DataLoaderDialog::~DataLoaderDialog()
{
    writeSettings();
}

std::vector<RealDataStruct> DataLoaderDialog::importedData() const
{
    return m_parsedData;
}

void DataLoaderDialog::setTargetCanvas(const std::vector<std::string>& canvas_names,
                                       int current_index)
{
    m_selectorPanel->setTargetCanvas(toStringList(canvas_names), current_index);
}

int DataLoaderDialog::targetCanvasIndex() const
{
    return m_selectorPanel->targetCanvasIndex();
}

void DataLoaderDialog::invokeFileSelectorDialog()
{
    m_selectorPanel->onAddFilesRequest();
}

void DataLoaderDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        return;
    QDialog::keyPressEvent(event);
}

void DataLoaderDialog::accept()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    process_all();
    QApplication::restoreOverrideCursor();

    QDialog::accept();
    close();
}

//! Saves dialog settings.

void DataLoaderDialog::readSettings()
{
    QSettings settings;

    if (settings.contains(dialogsize_setting_name()))
        resize(settings.value(dialogsize_setting_name(), QSize(800, 600)).toSize());

    if (settings.contains(splittersize_setting_name())) {
        QStringList splitter_sizes = QStringList() << "400"
                                                   << "400";
        splitter_sizes = settings.value(splittersize_setting_name(), splitter_sizes).toStringList();
        QList<int> sizes;
        for (auto num : splitter_sizes)
            sizes.push_back(num.toInt());
        m_splitter->setSizes(sizes);
    }
}

//! Writes dialog settings.

void DataLoaderDialog::writeSettings()
{
    QSettings settings;
    settings.setValue(dialogsize_setting_name(), size());

    QStringList splitter_sizes;
    for (auto x : m_splitter->sizes())
        splitter_sizes.push_back(QString::number(x));
    settings.setValue(splittersize_setting_name(), splitter_sizes);
}

//! Init interconnections of all widgets.

void DataLoaderDialog::init_connections()
{
    // connect toolbar and LoaderSelectorPanel
    connect(m_toolBar, &DataLoaderToolBar::addFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onAddFilesRequest);
    connect(m_toolBar, &DataLoaderToolBar::removeFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onRemoveFileRequest);

    // connect LoaderSelectorPanel with DataHandler
    auto on_file_list_changed = [this](const auto& container) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_dataHandler->updateRawData(toStringVector(container));
        QApplication::restoreOverrideCursor();
    };
    connect(m_selectorPanel, &LoaderSelectorPanel::fileNamesChanged, on_file_list_changed);

    connect(m_selectorPanel, &LoaderSelectorPanel::fileSelectionChanged,
            [this]() { process_data(); });

    connect(m_selectorPanel, &LoaderSelectorPanel::parserPropertyChanged,
            [this]() { process_data(); });
}

//! Process currently selected file with given parser settings.

void DataLoaderDialog::process_data()
{
    auto selected_files = m_selectorPanel->selectedFileNames();
    if (selected_files.empty())
        return;

    auto data_to_parse = m_dataHandler->textData(selected_files.back().toStdString());

    auto parser = m_selectorPanel->createParser();
    parser->process(data_to_parse);

    m_previewPanel->showData(parser.get());
}

//! Parse all string data and generate graph data.

void DataLoaderDialog::process_all()
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
