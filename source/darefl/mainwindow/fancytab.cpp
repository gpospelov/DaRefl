// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <darefl/mainwindow/fancytab.h>

FancyTab::FancyTab(const QString& title, QWidget* parent)
    : QWidget(parent), m_label(new QLabel(title))
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_label, 0, Qt::AlignCenter);
}

void FancyTab::setSelected(bool value)
{
    m_is_selected = value;
    update();
}

void FancyTab::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    if (m_is_selected)
        painter.drawLine(0, size().height()-2, size().width(), size().height()-2);
}

void FancyTab::mousePressEvent(QMouseEvent* event)
{
    if (isEnabled() && event->button() == Qt::LeftButton)
        clicked();
}
