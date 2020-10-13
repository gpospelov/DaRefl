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

class QSplitter;
class DataLoaderToolBar;
class LoaderSelectorPanel;
class LoaderPreviewPanel;

//! This is the main dialog for the data loader.

class DataLoaderDialogV2 : public QDialog
{
    Q_OBJECT

public:
    DataLoaderDialogV2(QWidget* parent = nullptr);

private:
    void init_connection();

    DataLoaderToolBar* m_toolBar{nullptr};
    LoaderSelectorPanel* m_selectorPanel{nullptr};
    LoaderPreviewPanel* m_previewPanel{nullptr};
    QSplitter* m_splitter{nullptr};
};

#endif // DAREFL_DATALOADER2_DATALOADERDIALOG_V2_H
