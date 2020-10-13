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

//! Panel with settings for DataLoaderDialog.
//! Located on its left side, contains file selection dialog and parsiong options.

class LoaderSelectorPanel : public QWidget
{
    Q_OBJECT

public:
    LoaderSelectorPanel(QWidget* parent = nullptr);
};

#endif // DAREFL_DATALOADER2_LOADERSELECTORPANEL_H
