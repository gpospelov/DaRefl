// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_WELCOMEVIEW_ADJUSTINGSCROLLAREA_H
#define DAREFL_WELCOMEVIEW_ADJUSTINGSCROLLAREA_H

#include <QScrollArea>

//! Modification of standard scroll area, which makes widget with dynamic layout occupy the whole
//! available space.

class AdjustingScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    AdjustingScrollArea(QWidget* parent = 0);
    void setWidget(QWidget* w);

    QSize sizeHint() const;

private:
    bool eventFilter(QObject* obj, QEvent* ev);
};

#endif // DAREFL_WELCOMEVIEW_ADJUSTINGSCROLLAREA_H
