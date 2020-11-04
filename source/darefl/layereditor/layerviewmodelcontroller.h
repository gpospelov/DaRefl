// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
#define DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H

#include <mvvm/viewmodel/viewmodelcontroller.h>

namespace ModelView
{
class ViewModel;
} // namespace ModelView

//! Controller for LayerViewModel to show MultiLayerItem in a tree with custom layout.
//! Will iterate through all top level items and creates rows with layer properties.

class LayerViewModelController : public ModelView::ViewModelController
{
public:
    LayerViewModelController(ModelView::SessionModel* model,
                                      ModelView::ViewModel* view_model);
};

#endif // DAREFL_LAYEREDITOR_LAYERVIEWMODELCONTROLLER_H
