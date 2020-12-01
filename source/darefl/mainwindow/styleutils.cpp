// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QFontMetrics>
#include <QSize>
#include <QToolBar>
#include <QWidget>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/resources/resources.h>

namespace DaRefl
{

QSize StyleUtils::ToolBarIconSize()
{
    return QSize(24, 24);
}

QSize StyleUtils::DockSizeHint()
{
    return QSize(480, 360);
}

QSize StyleUtils::DockMinimumSizeHint()
{
    return QSize(320, 240);
}

void StyleUtils::SetToolBarStyleTextBesides(QToolBar* toolbar)
{
    InitIconResources();
    toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

}
