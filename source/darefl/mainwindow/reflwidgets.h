// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MAINWINDOW_REFLWIDGETS_H
#define DAREFL_MAINWINDOW_REFLWIDGETS_H

#include <QWidget>

#include <darefl/materialeditor/materialeditor.h>

//! @file reflwidgets.h
//! Collection of placeholders for future reflectometry widgets.

//! Layer graphics scene.

class LayerCanvas : public QWidget
{
    Q_OBJECT
public:
    LayerCanvas(QWidget* parent = nullptr);
};

//! Instrument editor.

class InstrumentEditor : public QWidget
{
    Q_OBJECT
public:
    InstrumentEditor(QWidget* parent = nullptr);
};

#endif  // DAREFL_MAINWINDOW_REFLWIDGETS_H
