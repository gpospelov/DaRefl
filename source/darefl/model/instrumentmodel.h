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

//! Model to store specular instruments settings.

class InstrumentModel : public ModelView::SessionModel
{
public:
    InstrumentModel();
    InstrumentModel(std::shared_ptr<ModelView::ItemPool> pool);

private:
    void init_model();
};

#endif // DAREFL_MODEL_INSTRUMENTMODEL_H
