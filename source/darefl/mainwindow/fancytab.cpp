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
#include <QPainter>
#include <darefl/mainwindow/fancytab.h>

FancyTab::FancyTab(const QString& title, QWidget* parent)
    : QWidget(parent), m_label(new QLabel(title))
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_label, 0, Qt::AlignCenter);
}

void FancyTab::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawLine(0, 0, size().width(), 0);
}
