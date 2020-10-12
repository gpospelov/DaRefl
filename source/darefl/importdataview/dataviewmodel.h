// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_DATAVIEWMODEL_H
#define DAREFL_IMPORTDATAVIEW_DATAVIEWMODEL_H

#include <mvvm/viewmodel/topitemsviewmodel.h>

namespace ModelView
{
class SessionModel;
}

class ExperimentalDataModel;

//! This is the implementation of drag and drop support for the data editor

class DataViewModel : public ModelView::ViewModel
{
    Q_OBJECT
public:
    DataViewModel(ExperimentalDataModel* model, QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QMimeData* mimeData(const QModelIndexList& index_list) const override;
    Qt::DropActions supportedDragActions() const override;
    Qt::DropActions supportedDropActions() const override;
    bool canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                         const QModelIndex& parent) const override;
    bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                      const QModelIndex& parent) override;

private:
    ExperimentalDataModel* dataModel() const;
};

#endif // DAREFL_IMPORTDATAVIEW_DATAVIEWMODEL_H
