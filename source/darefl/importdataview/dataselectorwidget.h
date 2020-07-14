// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H
#define DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H

#include <QWidget>

//! Widget to select graphs and look at their properties.
//! Occupies the left part of ImportDataEditor.

class DataSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    DataSelectorWidget(QWidget* parent = nullptr);
};

#endif // DAREFL_IMPORTDATAVIEW_DATASELECTORWIDGET_H
