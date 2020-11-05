// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H
#define DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{
class SessionModel;
} // namespace ModelView

//! View model to display content of MultiLayerItem in table like views.

class LayerViewModel : public ModelView::ViewModel
{
    Q_OBJECT

public:
    LayerViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);
};

#endif // DAREFL_LAYEREDITOR_LAYERVIEWMODEL_H
