// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_INSTRUMENTMODEL_H
#define DAREFL_MODEL_INSTRUMENTMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <darefl/darefl_export.h>

//! Model to store specular instruments settings.

class DAREFLCORE_EXPORT InstrumentModel : public ModelView::SessionModel
{
public:
    InstrumentModel(std::shared_ptr<ModelView::ItemPool> pool = {});
};

#endif // DAREFL_MODEL_INSTRUMENTMODEL_H
