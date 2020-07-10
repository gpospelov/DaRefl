// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/importdatawidgets/datarowstrategy.h>
#include <darefl/importdatawidgets/dataviewmodel.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/realdatamodel.h>

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QMimeData>

#include <mvvm/factories/viewmodelcontrollerbuilder.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>
#include <mvvm/viewmodel/viewmodelutils.h>

#include <algorithm>

using namespace ModelView;

namespace
{
const QString LinkMimeType = "application/org.bornagainproject.fittinglink";

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
    return ViewModelControllerBuilder()
        .model(model)
        .viewModel(viewModel)
        .childrenStrategy(std::make_unique<TopItemsStrategy>())
        .rowStrategy(std::make_unique<DataRowStrategy>());
}

} // namespace


DataViewModel::DataViewModel(RealDataModel* model, QObject* parent)
    : ViewModel(createController(model, this), parent)
{
}

//! Return the Qt flags depending on the provided modelindex
Qt::ItemFlags DataViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = ViewModel::flags(index);

    if (index.isValid() && dataModel()->dragEnabled(sessionItemFromIndex(index)))
        defaultFlags = Qt::ItemIsDragEnabled | defaultFlags;

    if (dataModel()->dropEnabled(sessionItemFromIndex(index)))
        defaultFlags = Qt::ItemIsDropEnabled | defaultFlags;

    if (dataModel()->itemEditable(sessionItemFromIndex(index)))
        defaultFlags = Qt::ItemIsEditable | defaultFlags;

    return defaultFlags;
}

//! Generate the mime data
QMimeData* DataViewModel::mimeData(const QModelIndexList& index_list) const
{
    auto mimeData = new QMimeData;
    auto items = Utils::ItemsFromIndex(index_list);

    // Get the list of the identifiers
    QStringList identifiers;
    for (auto item : Utils::ItemsFromIndex(index_list))
        identifiers.append(QString::fromStdString(item->identifier()));

    mimeData->setData(QString::fromStdString(::Constants::RawDataMimeType), serialize(identifiers));
    return mimeData;
}

//! Supported drag actions
Qt::DropActions DataViewModel::supportedDragActions() const
{
    return Qt::TargetMoveAction;
}

//! Supported drop actions
Qt::DropActions DataViewModel::supportedDropActions() const
{
    return Qt::TargetMoveAction;
}

bool DataViewModel::canDropMimeData(const QMimeData* data, Qt::DropAction, int, int,
                                    const QModelIndex&) const
{
    if (!data->hasFormat(QString::fromStdString(::Constants::RawDataMimeType)))
        return false;

    return true;
}

bool DataViewModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                 const QModelIndex& parent)
{
    if (!canDropMimeData(data, action, row, column, parent))
        return false;

    int requested_row = parent.isValid() ? parent.row() : row;
    // retrieving list of item identifiers and accessing items
    auto identifiers =
        deserialize(data->data(QString::fromStdString(::Constants::RawDataMimeType)));
    for (auto id : identifiers) {
        auto item = sessionModel()->findItem(id.toStdString());
        auto tag = item->tag();
        int row = std::clamp(
            requested_row, 0,
            sessionItemFromIndex(parent)->itemCount(sessionItemFromIndex(parent)->defaultTag())
                - 1);
        if (!dataModel()->dragDropItem(item, sessionItemFromIndex(parent), row))
            return false;
    }

    return true;
}

RealDataModel* DataViewModel::dataModel() const
{
    return dynamic_cast<RealDataModel*>(sessionModel());
}
