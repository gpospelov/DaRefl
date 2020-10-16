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
class ParserPropertyWidget;

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

signals:
    void fileNamesChanged(const QStringList& file_names);
    void fileSelectionChanged(const QStringList& file_names);

private:
    void init_connections();

    ImportFileWidgetV2* m_fileSelectorWidget{nullptr};
    ParserPropertyWidget* m_propertyWidget{nullptr};
};

#endif // DAREFL_DATALOADER2_LOADERSELECTORPANEL_H
