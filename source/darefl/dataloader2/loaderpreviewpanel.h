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

//! Panel with settings for DataLoaderDialog.
//! Located on its right side, contains text and table views.

class LoaderPreviewPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderPreviewPanel(QWidget* parent = nullptr);
};

#endif // DAREFL_DATALOADER2_LOADERPREVIEW_H
