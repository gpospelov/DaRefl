// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_IMPORTFILEWIDGET_V2_H
#define DAREFL_DATALOADER2_IMPORTFILEWIDGET_V2_H

#include <QWidget>

class QListView;
class QStringListModel;

//! Contains list of files to import. Part of LoaderPreviewPanel.

class ImportFileWidgetV2 : public QWidget
{
    Q_OBJECT

public:
    ImportFileWidgetV2(QWidget* parent = nullptr);

public slots:
    void onAddFilesRequest();
    void onRemoveFileRequest();

    QStringList fileNames() const;

    QStringList selectedFileNames() const;

signals:
    void fileNamesChanged();
    void fileSelectionChanged();

private:
    void updateCurrentWorkdir(const QStringList& file_names);
    void addFileNamesToModel(const QStringList& file_names);

    QListView* m_listView{nullptr};
    QStringListModel* m_listModel{nullptr};
    QString m_currentWorkdir;
};

#endif // DAREFL_DATALOADER2_IMPORTFILEWIDGET_V2_H
