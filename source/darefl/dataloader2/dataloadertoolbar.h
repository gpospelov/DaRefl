// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER2_DATALOADERTOOLBAR_H
#define DAREFL_DATALOADER2_DATALOADERTOOLBAR_H

#include <QToolBar>

class QComboBox;

class DataLoaderToolBar : public QToolBar
{
    Q_OBJECT

public:
    DataLoaderToolBar(QWidget* parent = nullptr);

signals:
    void addFilesRequest();
    void removeFilesRequest();

private:

};

#endif // DAREFL_DATALOADER2_DATALOADERTOOLBAR_H
