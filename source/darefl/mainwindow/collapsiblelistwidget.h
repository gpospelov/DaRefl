// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_COLLAPSIBLELISTWIDGET_H
#define DAREFL_IMPORTDATAVIEW_COLLAPSIBLELISTWIDGET_H

#include <QWidget>

class QSplitter;
class QString;

//! Vertical widget with column of panels displayed one under another.
//! Each panel contains user widget and can be collapsed/expanded. When expanded,
//! the place occupied by the panel can be changed by draging a splitter.

class CollapsibleListWidget : public QWidget
{
    Q_OBJECT
public:
    CollapsibleListWidget(QWidget* parent = nullptr);

    void addWidget(QWidget* widget, const QString& title, bool collapsed = false);

private:
    QSplitter* m_splitter{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_COLLAPSIBLELISTWIDGET_H
