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
    : EditorWidget(parent), graph_canvas(new ModelView::GraphCanvas)
{
    p_toolbar = dynamic_cast<EditorToolBar*>(new GraphEditorToolBar);
    p_toolbar->setToggleWidget(graph_canvas);
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(graph_canvas);
    layout->addWidget(p_toolbar);

    connect(dynamic_cast<GraphEditorToolBar*>(p_toolbar), &GraphEditorToolBar::resetViewport,
            [this]() { graph_canvas->update_viewport(); });
}

void GraphEditor::setItem(ModelView::GraphViewportItem* viewport_item)
{
    graph_canvas->setItem(viewport_item);
}
