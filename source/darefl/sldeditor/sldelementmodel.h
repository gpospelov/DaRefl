// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDELEMENTMODEL_H
#define DAREFL_SLDEDITOR_SLDELEMENTMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

// The mvvm session item associated to a layer
class LayerElementItem;

namespace ModelView
{
class ExternalProperty;
}

//! The model of the sld layer visual representation
class SLDElementModel : public ModelView::SessionModel
{
public:
    SLDElementModel();

    //! Add a layer item
    LayerElementItem* addLayer();
};

#endif  // DAREFL_SLDEDITOR_SLDELEMENTMODEL_H
