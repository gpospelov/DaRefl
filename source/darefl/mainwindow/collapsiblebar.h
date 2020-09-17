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

#include <QFrame>

class QLabel;
class QString;

//! Horizontal collapsible bar, part of CollapsibleListWidget.
//! It is intended for placement into the QSplitter and makes visible/invisible client widget
//! on clicks.

class CollapsibleBar : public QFrame
{
    Q_OBJECT
public:
    CollapsibleBar(QWidget* parent = nullptr);

    void setWidget(QWidget* widget, const QString& title);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void updatePixmap();

    QWidget* m_controlledWidget{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QLabel* m_titleLabel{nullptr};
};

#endif // DAREFL_IMPORTDATAVIEW_COLLAPSIBLEBAR_H
