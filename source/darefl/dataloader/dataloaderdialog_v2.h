// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_DATALOADERDIALOG_V2_H
#define DAREFL_DATALOADER2_DATALOADERDIALOG_V2_H

#include <QDialog>
#include <memory>
#include <vector>
#include <darefl/model/experimentaldata_types.h>

class QSplitter;
class DataLoaderToolBar;
class LoaderSelectorPanel;
class LoaderPreviewPanel;
class DataHandler;

//! This is the main dialog for the data loader.

class DataLoaderDialogV2 : public QDialog
{
    Q_OBJECT

public:
    DataLoaderDialogV2(QWidget* parent = nullptr);
    ~DataLoaderDialogV2();

    std::vector<RealDataStruct> importedData() const;

    void setTargetCanvas(const std::vector<std::string>& canvas_names, int current_index);

    int targetCanvasIndex() const;

    void invokeFileSelectorDialog();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void accept() override;

private:
    void readSettings();
    void writeSettings();

    void init_connections();
    void process_data();
    void process_all();

    DataLoaderToolBar* m_toolBar{nullptr};
    LoaderSelectorPanel* m_selectorPanel{nullptr};
    LoaderPreviewPanel* m_previewPanel{nullptr};
    QSplitter* m_splitter{nullptr};

    std::unique_ptr<DataHandler> m_dataHandler;
    std::vector<RealDataStruct> m_parsedData;
};

#endif // DAREFL_DATALOADER2_DATALOADERDIALOG_V2_H
