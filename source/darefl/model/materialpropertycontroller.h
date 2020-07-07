// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_MATERIALPROPERTYCONTROLLER_H
#define DAREFL_MODEL_MATERIALPROPERTYCONTROLLER_H

#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modellistener.h>

class SampleModel;
class MaterialModel;

//! Listens for all changes in material model and updates properties in SampleModel.

class MaterialPropertyController : public ModelView::ModelListener<MaterialModel>
{
public:
    MaterialPropertyController(MaterialModel* material_model, SampleModel* sample_model);

private:
    void update_all();

    SampleModel* m_sample_model{nullptr};
};

#endif // DAREFL_MODEL_MATERIALPROPERTYCONTROLLER_H
