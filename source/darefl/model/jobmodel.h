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
class Data1DItem;
class GraphViewportItem;
} // namespace ModelView

class JobItem;
class CanvasItem;
class SpecularInstrumentItem;

struct SimulationResult;
struct SLDProfile;

//! Contains results of quick reflectometry simulations.
class JobModel : public ModelView::SessionModel
{
public:
    JobModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    ModelView::Data1DItem* sldData() const;
    ModelView::GraphViewportItem* sldViewport() const;

    ModelView::Data1DItem* specularData() const;

    CanvasItem* specularViewport() const;

    void updateReferenceGraphFrom(const SpecularInstrumentItem* instrument);

    void updateSpecularData(const SimulationResult& data);

    void updateSLDProfile(const SLDProfile& data);

private:
    JobItem* jobItem() const;
};

#endif // DAREFL_MODEL_JOBMODEL_H
