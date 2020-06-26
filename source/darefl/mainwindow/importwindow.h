// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_IMPORTWINDOW_H
#define DAREFL_MAINWINDOW_IMPORTWINDOW_H

#include <QWidget>

class ApplicationModels;

//! Main window to import user data.

class ImportWindow : public QWidget
{
    Q_OBJECT
public:
    ImportWindow(ApplicationModels* models, QWidget* parent = nullptr);

private:
    ApplicationModels* models{nullptr};
};

#endif  // DAREFL_MAINWINDOW_IMPORTWINDOW_H
