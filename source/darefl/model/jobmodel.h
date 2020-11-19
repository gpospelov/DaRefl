// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_JOBMODEL_H
#define DAREFL_MODEL_JOBMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView
{
class GraphViewportItem;
class GraphItem;
} // namespace ModelView

class JobItem;
class CanvasItem;
struct SimulationResult;
struct SLDProfile;

//! The model to store results of (possibly) multiple reflectometry simulation, and all
//! viewports, representing various graphs in QuickSimEditor widgets.

class JobModel : public ModelView::SessionModel
{
public:
    JobModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    ModelView::GraphViewportItem* sldViewport() const;

    CanvasItem* specularViewport() const;

    ModelView::GraphViewportItem* diffViewport() const;

    void updateReferenceGraph(const ModelView::GraphItem* graph);

    void updateSpecularData(const SimulationResult& data);

    void updateSLDProfile(const SLDProfile& data);

private:
    JobItem* jobItem() const;
};

#endif // DAREFL_MODEL_JOBMODEL_H
