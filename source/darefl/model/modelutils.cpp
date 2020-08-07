// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/modelutils.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/standarditems/graphitem.h>

ModelView::ExternalProperty Utils::CreateProperty(const ModelView::GraphItem* graph)
{
    std::string name = graph->parent()->displayName() + "/" + graph->displayName();
    auto color = graph->property<QColor>(ModelView::GraphItem::P_COLOR);
    return ModelView::ExternalProperty(name, color, graph->identifier());
}
