// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_LOADERPREVIEWPANEL_H
#define DAREFL_DATALOADER_LOADERPREVIEWPANEL_H

#include <QWidget>

class ImportTextView;
class ImportTableWidget;
class QTabWidget;

namespace DataLoader
{
class ParserInterface;
struct ColumnInfo;
} // namespace DataLoader

//! Panel with settings for DataLoaderDialog.
//! Located on its right side, contains text and table views.

class LoaderPreviewPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderPreviewPanel(QWidget* parent = nullptr);

    void showData(const DataLoader::ParserInterface* parser);

    std::vector<DataLoader::ColumnInfo> columnInfo() const;

private:
    ImportTextView* m_textView{nullptr};
    ImportTableWidget* m_tableWidget{nullptr};
    QTabWidget* m_tabWidget{nullptr};
};

#endif // DAREFL_DATALOADER_LOADERPREVIEWPANEL_H
