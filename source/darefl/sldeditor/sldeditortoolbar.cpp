// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QAction>
#include <QToolButton>
#include <darefl/mainwindow/styleutils.h>
#include <darefl/resources/resources.h>
#include <darefl/sldeditor/sldeditoractions.h>
#include <darefl/sldeditor/sldeditortoolbar.h>

namespace DaRefl
{

SLDEditorToolBar::SLDEditorToolBar(SLDEditorActions* actions, QWidget* parent) : QToolBar(parent)
{
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto reset_view = new QToolButton;
    reset_view->setToolTip("Set axes to default range.");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    addWidget(reset_view);
    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}

} // namespace DaRefl
