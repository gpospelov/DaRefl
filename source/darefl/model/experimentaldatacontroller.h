// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_EXPERIMENTALDATACONTROLLER_H
#define DAREFL_MODEL_EXPERIMENTALDATACONTROLLER_H

#include <darefl/darefl_export.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/modellistener.h>

namespace DaRefl
{

class InstrumentModel;
class ExperimentalDataModel;

//! Listens for all changes in ExperimentalDataModel and updates properties in InstrumentModel.
//! Main task is to update links of ExperimentalScanItem to particular imported graph, when
//! ExperimentalDataModel is changing.

class DAREFLCORE_EXPORT ExperimentalDataController
    : public ModelView::ModelListener<ExperimentalDataModel>
{
public:
    ExperimentalDataController(ExperimentalDataModel* data_model,
                               InstrumentModel* instrument_model);

private:
    void update_all();

    InstrumentModel* m_instrument_model{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_MODEL_EXPERIMENTALDATACONTROLLER_H
