// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_SAMPLEMODEL_H
#define DAREFL_MODEL_SAMPLEMODEL_H

#include <mvvm/model/sessionmodel.h>

//! Model to hold layers and multi-layers.
class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();
    SampleModel(std::shared_ptr<ModelView::ItemPool> pool);

    void create_default_multilayer();

private:
    void init_model();
};

#endif // DAREFL_MODEL_SAMPLEMODEL_H
