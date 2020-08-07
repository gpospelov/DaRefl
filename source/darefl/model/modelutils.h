// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_MODELUTILS_H
#define DAREFL_MODEL_MODELUTILS_H

namespace ModelView
{
class GraphItem;
class ExternalProperty;
} // namespace ModelView

namespace Utils
{

//! Returns property representing given graph.
//! Used to link with the graph from various editors.

ModelView::ExternalProperty CreateProperty(const ModelView::GraphItem* graph);

} // namespace Utils

#endif // DAREFL_MODEL_MODELUTILS_H
