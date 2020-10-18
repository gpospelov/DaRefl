// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_LOADERPREVIEW_H
#define DAREFL_DATALOADER2_LOADERPREVIEW_H

#include <QWidget>

class ImportTextViewV2;
class ImportTableWidget;
class QTabWidget;

namespace DataLoader
{
class ParserInterface;
}

//! Panel with settings for DataLoaderDialog.
//! Located on its right side, contains text and table views.

class LoaderPreviewPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderPreviewPanel(QWidget* parent = nullptr);

    void setTextData(const std::vector<std::string>& textData);
    void showData(const DataLoader::ParserInterface* parser);

private:
    ImportTextViewV2* m_textView{nullptr};
    ImportTableWidget* m_tableWidget{nullptr};
    QTabWidget* m_tabWidget{nullptr};
};

#endif // DAREFL_DATALOADER2_LOADERPREVIEW_H
