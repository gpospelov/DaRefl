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

#include <vector>
#include <string>

namespace ModelView
{
class GraphItem;
class ExternalProperty;
} // namespace ModelView

class ExperimentalDataModel;

namespace Utils
{

//! Returns property representing given graph.
//! Used to link with the graph from various editors.
ModelView::ExternalProperty CreateProperty(const ModelView::GraphItem* graph);

//! Returns vector of properties representing GraphItem content of the model.
std::vector<ModelView::ExternalProperty> CreateGraphProperties(ExperimentalDataModel* model);

//! Finds the property with the same `id` in given vector and returns it.
ModelView::ExternalProperty FindProperty(const std::vector<ModelView::ExternalProperty>& properties,
                                         const std::string& id);

} // namespace Utils

#endif // DAREFL_MODEL_MODELUTILS_H
