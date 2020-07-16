// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAWIDGETS_DATAROWSTRATEGY_H
#define DAREFL_IMPORTDATAWIDGETS_DATAROWSTRATEGY_H

#include <memory>
#include <mvvm/interfaces/rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{
class SessionItem;
}

//! Constructs the row strategy for the given data view model controller

class DataRowStrategy : public ModelView::RowStrategyInterface
{
public:
    QStringList horizontalHeaderLabels() const override;

    std::vector<std::unique_ptr<ModelView::ViewItem>>
    constructRow(ModelView::SessionItem*) override;
};

#endif // DAREFL_IMPORTDATAWIDGETS_DATAROWSTRATEGY_H
