// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHBoxLayout>
#include <darefl/grapheditor/grapheditor.h>
#include <darefl/grapheditor/grapheditortoolbar.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/graphviewportitem.h>

GraphEditor::GraphEditor(QWidget* parent)
    : QWidget(parent), toolbar(new GraphEditorToolBar), graph_canvas(new ModelView::GraphCanvas)
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(graph_canvas);
    layout->addWidget(toolbar);

    connect(toolbar, &GraphEditorToolBar::resetViewport,
            [this]() { graph_canvas->update_viewport(); });
}

void GraphEditor::setItem(ModelView::GraphViewportItem* viewport_item)
{
    graph_canvas->setItem(viewport_item);
}
