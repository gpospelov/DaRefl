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
#include <memory>

namespace DataLoader
{
class ParserInterface;
}

class ImportFileWidgetV2;
class ParserPropertyWidget;

//! Panel with settings for DataLoaderDialog.
//! Located on its left side, contains file selection dialog and parser property widget.

class LoaderSelectorPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderSelectorPanel(QWidget* parent = nullptr);
    ~LoaderSelectorPanel();

    std::unique_ptr<DataLoader::ParserInterface> createParser() const;

public slots:
    void onAddFilesRequest();
    void onRemoveFileRequest();
    QStringList selectedFileNames() const;
    QStringList fileNames() const;

signals:
    void fileNamesChanged(const QStringList& file_names);
    void fileSelectionChanged(const QStringList& file_names);
    void parserPropertyChanged();

private:
    void init_connections();

    ImportFileWidgetV2* m_fileSelectorWidget{nullptr};
    ParserPropertyWidget* m_propertyWidget{nullptr};
};

#endif // DAREFL_DATALOADER2_LOADERSELECTORPANEL_H
