// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_COLLAPSIBLEBAR_H
#define DAREFL_IMPORTDATAVIEW_COLLAPSIBLEBAR_H

#include <QWidget>

class QLabel;
class QString;

//! Horizontal collapsible bar, part of CollapsibleListWidget.
//! It is intended for placement into the QSplitter and makes visible/invisible client widget
//! on clicks.

class CollapsibleBar : public QWidget
{
    Q_OBJECT
public:
    CollapsibleBar(QWidget* parent = nullptr);

    void setWidget(QWidget* widget, const QString& title);

private:
    QWidget* m_controlledWidget{nullptr};
    QLabel* m_label{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_COLLAPSIBLEBAR_H
