// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
#define DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H

#include <QWidget>

//! Widget to show canvas with graph collection.
//! Occupies the right part of ImportDataEditor.

class GraphCanvasWidget : public QWidget
{
    Q_OBJECT
public:
    GraphCanvasWidget(QWidget* parent = nullptr);
};

#endif // DAREFL_IMPORTDATAVIEW_GRAPHCANVASWIDGET_H
