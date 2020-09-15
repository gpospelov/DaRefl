// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_JOBITEM_H
#define DAREFL_MODEL_JOBITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/standarditems/graphviewportitem.h>

namespace ModelView
{
class Data1DItem;
class GraphViewportItem;
} // namespace ModelView

class CanvasItem;
class SpecularInstrumentItem;

//! Viewport intended for showing SLD profile.
//! Provides custom y-axis range.

class SLDCanvasItem : public ModelView::GraphViewportItem
{
public:
    SLDCanvasItem();

protected:
    std::pair<double, double> data_yaxis_range() const override;
};

//! Holds results of toy reflectivity simulation.

class JobItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_SLD_DATA = "P_SLD_DATA";
    static inline const std::string P_SLD_VIEWPORT = "P_SLD_VIEWPORT";
    static inline const std::string P_SPECULAR_DATA = "P_SPECULAR_DATA";
    static inline const std::string P_SPECULAR_VIEWPORT = "P_SPECULAR_VIEWPORT";

    JobItem();

    ModelView::Data1DItem* sld_data() const;
    SLDCanvasItem* sld_viewport() const;

    ModelView::Data1DItem* specular_data() const;
    CanvasItem* specular_viewport() const;

    ModelView::GraphItem* referenceGraph() const;

    void updateReferenceGraphFrom(const SpecularInstrumentItem* instrument);

private:
    void setup_graph(const std::string& data_tag, const std::string& viewport_tag);
    void setup_sld_viewport();
    void setup_specular_viewport();
    void setup_reference_graph();
};

#endif // DAREFL_MODEL_JOBITEM_H
