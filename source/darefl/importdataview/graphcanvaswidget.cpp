// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QVBoxLayout>
#include <darefl/importdataview/graphcanvaswidget.h>
#include <darefl/model/experimentaldataitems.h>
#include <mvvm/plotting/graphcanvas.h>

GraphCanvasWidget::GraphCanvasWidget(QWidget* parent)
    : QWidget(parent), m_graphCanvas(new ModelView::GraphCanvas)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphCanvas);
}

void GraphCanvasWidget::setItem(CanvasItem* canvas_item)
{
    m_graphCanvas->setItem(canvas_item);
}

void GraphCanvasWidget::updateViewport()
{
    m_graphCanvas->update_viewport();
}
