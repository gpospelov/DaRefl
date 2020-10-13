// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_LOADERSELECTORPANEL_H
#define DAREFL_DATALOADER2_LOADERSELECTORPANEL_H

#include <QWidget>

class ImportFileWidgetV2;

//! Panel with settings for DataLoaderDialog.
//! Located on its left side, contains file selection dialog and parsiong options.

class LoaderSelectorPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderSelectorPanel(QWidget* parent = nullptr);

public slots:
    void onAddFilesRequest();
    void onRemoveFileRequest();
    std::vector<std::string> fileNames() const;

signals:
    void fileNamesChanged();

private:
    ImportFileWidgetV2* m_fileSelectorWidget{nullptr};
};

#endif // DAREFL_DATALOADER2_LOADERSELECTORPANEL_H
