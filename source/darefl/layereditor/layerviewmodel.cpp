// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/layereditor/layerviewmodel.h>
#include <darefl/layereditor/layerviewmodelcontroller.h>

using namespace ModelView;

LayerViewModel::LayerViewModel(SessionModel* model, QObject* parent)
    : ViewModel(std::make_unique<LayerViewModelController>(model, this), parent)
{
}
