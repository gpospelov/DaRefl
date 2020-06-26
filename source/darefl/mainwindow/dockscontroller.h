// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_DOCKSCONTROLLER_H
#define DAREFL_MAINWINDOW_DOCKSCONTROLLER_H

#include <QObject>
#include <memory>

class QMainWindow;

//! Handles appearance of docked widgets in the QMainWindow context.

class DocksController : public QObject
{
    Q_OBJECT

public:
    DocksController(QMainWindow* main_window);
    ~DocksController();

    void addWidget(int index, QWidget* widget, Qt::DockWidgetArea area);

private:
    struct DocksControllerImpl;
    std::unique_ptr<DocksControllerImpl> p_impl;
};

#endif  // DAREFL_MAINWINDOW_DOCKSCONTROLLER_H
