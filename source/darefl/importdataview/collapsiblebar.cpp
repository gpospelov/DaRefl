// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QLabel>
#include <QVBoxLayout>
#include <darefl/importdataview/collapsiblebar.h>
#include <mvvm/widgets/widgetutils.h>

CollapsibleBar::CollapsibleBar(QWidget* parent) : QWidget(parent), m_label(new QLabel)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_label);

    setFixedHeight(ModelView::Utils::HeightOfLetterM()*2);
}

void CollapsibleBar::setWidget(QWidget* widget, const QString& title)
{
    m_controlledWidget = widget;
    m_label->setText(title);
}
