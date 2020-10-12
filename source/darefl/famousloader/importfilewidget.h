// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_FAMOUSLOADER_IMPORTFILEWIDGET_H
#define DAREFL_FAMOUSLOADER_IMPORTFILEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListView;
class QStringListModel;
class QItemSelection;
class QSettings;
QT_END_NAMESPACE

namespace DataImportGui
{

//! This is the main dialog for the data loader
class ImportFileWidget : public QWidget
{
    Q_OBJECT

public:
    ImportFileWidget(QWidget* parent = nullptr);
    ~ImportFileWidget() = default;

    int currentSelection() const;

    void readSettings();
    void writeSettings();
    void addFiles();

signals:
    void filesChanged(std::vector<std::string> files);
    void selectionChanged();

private:
    void createWidgets();
    void resetFiles();
    std::vector<std::string> currentFiles() const;

private:
    QListView* m_listView{nullptr};
    QStringListModel* m_listModel{nullptr};
    QString m_defaultPath{""};
};

} // End of namespace DataImportGui

#endif // DAREFL_FAMOUSLOADER_IMPORTFILEWIDGET_H
