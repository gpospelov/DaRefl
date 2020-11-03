// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/importdataview/datarowstrategy.h>
#include <darefl/importdataview/dataviewmodel.h>
#include <darefl/model/experimentaldatamodel.h>
#include <darefl/model/item_constants.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>

#include <mvvm/factories/viewmodelcontrollerfactory.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/standardviewmodelcontrollers.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelutils.h>

#include <algorithm>

using namespace ModelView;

namespace
{
const std::string RawDataMimeType = "quickrefl/moveDataItem";

// FIXME move functions to ,mvvm/widget/widgetutils>

QByteArray serialize(const QStringList& data)
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out << data;
    return byteArray;
}

QStringList deserialize(QByteArray byteArray)
{
    QStringList result;
    QDataStream in(&byteArray, QIODevice::ReadOnly);
    in >> result;
    return result;
}

std::unique_ptr<ViewModelController> createController(SessionModel* model, ViewModelBase* viewModel)
{
    return Factory::CreateController<TopItemsStrategy, DataRowStrategy>(model, viewModel);
}

} // namespace

DataViewModel::DataViewModel(ExperimentalDataModel* model, QObject* parent)
    //    : ViewModel(createController(model, this), parent)
    : ViewModel(std::make_unique<TopItemsViewModelController>(model, this), parent)
{
}

//! Return the Qt flags for given index. We allow GraphItem drag, they can be dropped on CanvasItem.

Qt::ItemFlags DataViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result = ViewModel::flags(index);

    if (auto item = sessionItemFromIndex(index); item) {
        if (item->modelType() == ModelView::Constants::GraphItemType)
            result |= Qt::ItemIsDragEnabled;
        else if (item->modelType() == ::Constants::CanvasItemType)
            result |= Qt::ItemIsDropEnabled;
    }

    return result;
}

//! Generate the mime data for all selected items.

QMimeData* DataViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto result = new QMimeData;

    // Get the list of the identifiers
    QStringList identifiers;
    for (auto item : Utils::UniqueItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    result->setData(QString::fromStdString(RawDataMimeType), serialize(identifiers));

    return result;
}

//! Supported drag actions.

Qt::DropActions DataViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

//! Supported drop actions.

Qt::DropActions DataViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

//! Returns true if we can drop item here.

bool DataViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row,
                                    int column, const QModelIndex& parent) const
{
    qDebug() << "DragViewModel::canDropMimeData" << data << action << row << column << parent;
    bool result{false};
    if (data->hasFormat(QString::fromStdString(RawDataMimeType)))
        if (auto target = sessionItemFromIndex(parent); target)
            result = target->modelType() == ::Constants::CanvasItemType;

    qDebug() << "           can drop?" << result;

    return result;
}

bool DataViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    auto target = sessionItemFromIndex(parent);

    int requested_row = parent.isValid() ? parent.row() : row;

    qDebug() << "DragViewModel::dropMimeData" << data << action << row << column << "parent" << parent << "target" << target << "requested_row" << requested_row;

    // retrieving list of item identifiers and accessing items
    auto identifiers = deserialize(data->data(QString::fromStdString(RawDataMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());

        int row = std::clamp(requested_row, 0, item->parent()->itemCount(item->tag()) - 1);
        qDebug() << "going to move" << id << item << QString::fromStdString(item->modelType())
                 << "requested_row" << requested_row << row;
        sessionModel()->moveItem(item, target, {"", row});
    }

    return true;
}

// ExperimentalDataModel* DataViewModel::dataModel() const
//{
//    return dynamic_cast<ExperimentalDataModel*>(sessionModel());
//}
