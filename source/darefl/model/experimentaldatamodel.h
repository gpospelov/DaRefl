// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_EXPERIMENTALDATAMODEL_H
#define DAREFL_MODEL_EXPERIMENTALDATAMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

class CanvasContainerItem;
class ExperimentalDataContainerItem;
class CanvasItem;
class RealDataStruct;

namespace ModelView
{
class SessionItem;
class GraphItem;
class GraphViewportItem;
} // namespace ModelView

//! The model to store imported reflectometry data.

class ExperimentalDataModel : public ModelView::SessionModel
{
public:
    using name_identifier_t = std::pair<std::string, std::string>;
    ExperimentalDataModel();

    CanvasItem* addDataToCollection(RealDataStruct data_struct, CanvasContainerItem* data_node,
                                    CanvasItem* data_group = nullptr);
    void removeAllDataFromCollection(CanvasContainerItem* data_node);
    void removeDataFromCollection(std::vector<ModelView::SessionItem*> item_to_remove);
    std::vector<name_identifier_t> availableCanvasesInfo() const;

    bool checkAllGroup(std::vector<ModelView::SessionItem*>& items) const;
    ModelView::GraphViewportItem* checkAllGraph(std::vector<ModelView::SessionItem*>& items) const;
    bool itemEditable(ModelView::SessionItem* item) const;
    bool dragEnabled(ModelView::SessionItem* item) const;
    bool dropEnabled(ModelView::SessionItem* item) const;
    bool dragDropItem(ModelView::SessionItem* item, ModelView::SessionItem* target, int row = -1);
    bool mergeItems(std::vector<ModelView::SessionItem*> items);

    CanvasContainerItem* canvasContainer() const;

private:
    ExperimentalDataContainerItem* dataContainer() const;

    void addDataToGroup(CanvasItem* data_group, RealDataStruct& data_struct);
    void removeDataFromGroup(ModelView::GraphItem* item);
};

#endif // DAREFL_MODEL_EXPERIMENTALDATAMODEL_H
