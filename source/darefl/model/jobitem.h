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
    static inline const std::string P_DIFF_DATA = "P_DIFF_DATA";
    static inline const std::string P_DIFF_VIEWPORT = "P_DIFF_VIEWPORT";

    JobItem();

    ModelView::Data1DItem* sldData() const;
    SLDCanvasItem* sldViewport() const;

    ModelView::Data1DItem* specularData() const;
    CanvasItem* specularViewport() const;

    void updateReferenceGraphFrom(const SpecularInstrumentItem* instrument);

private:
    ModelView::GraphItem* specularGraph() const;
    ModelView::GraphItem* referenceGraph() const;

    void setup_sld_viewport();
    void setup_specular_viewport();
    void setup_diff_viewport();
};

#endif // DAREFL_MODEL_JOBITEM_H
