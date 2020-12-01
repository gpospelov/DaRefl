// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementcontroller.h>

#include <darefl/sldeditor/graphicsscene.h>
#include <darefl/sldeditor/handleelementview.h>
#include <darefl/sldeditor/layerelementitem.h>
#include <darefl/sldeditor/roughnesselementview.h>
#include <darefl/sldeditor/segmentelementview.h>

#include <mvvm/signals/itemmapper.h>
#include <stdexcept>
#include <string>

using namespace ModelView;

namespace DaRefl
{

//! Constructor
LayerElementController::LayerElementController(LayerElementItem* layer_view_item)
    : QObject(), p_model_item(layer_view_item), m_sample_item_id(" ")
{
}

//! Returns the pointer to the LayerElementItem in the model
LayerElementItem* LayerElementController::layerElementItem() const
{
    return p_model_item;
}

//! Allow the population of the own elements
void LayerElementController::autoPopulate()
{
    setSideSegment(new SegmentElementView());
    setTopSegment(new SegmentElementView());
    setSegmentHandles(new HandleElementView(), new HandleElementView());
    setRoughness(new RoughnessElementView());
    setRoughnessHandles(new HandleElementView(), new HandleElementView());
}

//! If loacally created the view elements nees to be locally destroyed
void LayerElementController::deleteViewItems()
{
    if (m_segment_views[0]) {
        auto temp_ptr = m_segment_views[0];
        unsetSideSegment();
        delete temp_ptr;
    }
    if (m_segment_views[1]) {
        auto temp_ptr = m_segment_views[1];
        unsetTopSegment();
        delete temp_ptr;
    }
    if (m_handle_views[0]) {
        auto temp_ptr_0 = m_handle_views[0];
        auto temp_ptr_1 = m_handle_views[1];
        unsetSegmentHandles();
        delete temp_ptr_0;
        delete temp_ptr_1;
    }
    if (p_roughness_view) {
        auto temp_ptr = p_roughness_view;
        unsetRoughness();
        delete temp_ptr;
    }
    if (m_rough_handles_views[0]) {
        auto temp_ptr_0 = m_rough_handles_views[0];
        auto temp_ptr_1 = m_rough_handles_views[1];
        unsetRoughnessHandles();
        delete temp_ptr_0;
        delete temp_ptr_1;
    }
}

//! Connect to the set item
void LayerElementController::connectToModel() const
{
    auto on_property_change = [this](ModelView::SessionItem* item, std::string property_name) {
        if (property_name == LayerElementItem::P_X_POS) {
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
            updateRoughness();
            if (layerBelow())
                layerBelow()->layerElementItem()->setProperty(
                    LayerElementItem::P_X_POS,
                    layerElementItem()->property<double>(LayerElementItem::P_X_POS)
                        + layerElementItem()->property<double>(LayerElementItem::P_WIDTH));
        }
        if (property_name == LayerElementItem::P_HEIGHT) {
            emit heightChanged(m_sample_item_id,
                               layerElementItem()->property<double>(LayerElementItem::P_HEIGHT));
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
            updateRoughness();
            if (layerBelow()) {
                layerBelow()->updateSideSegment();
                layerBelow()->updateSegmentHandles();
                layerBelow()->updateRoughness();
            }
        }
        if (property_name == LayerElementItem::P_WIDTH) {
            emit widthChanged(m_sample_item_id,
                              layerElementItem()->property<double>(LayerElementItem::P_WIDTH));
            updateSideSegment();
            updateTopSegment();
            updateSegmentHandles();
            updateRoughness();
            if (layerBelow())
                layerBelow()->layerElementItem()->setProperty(
                    LayerElementItem::P_X_POS,
                    layerElementItem()->property<double>(LayerElementItem::P_X_POS)
                        + layerElementItem()->property<double>(LayerElementItem::P_WIDTH));
        }
        if (property_name == LayerElementItem::P_ROUGHNESS) {
            emit roughnessChanged(m_sample_item_id, layerElementItem()->property<double>(
                                                        LayerElementItem::P_ROUGHNESS));
            updateRoughness();
        }

        // Side segment update
        if (property_name == LayerElementItem::P_SIDE_THICKNESS) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_PEN_WIDTH) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_PEN_COLOR) {
            updateSideSegment();
        }
        if (property_name == LayerElementItem::P_SIDE_BRUSH_COLOR) {
            updateSideSegment();
        }

        // Top segment update
        if (property_name == LayerElementItem::P_TOP_THICKNESS) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_PEN_WIDTH) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_PEN_COLOR) {
            updateTopSegment();
        }
        if (property_name == LayerElementItem::P_TOP_BRUSH_COLOR) {
            updateTopSegment();
        }

        // Segment handle update
        if (property_name == LayerElementItem::P_HANDLE_RADIUS) {
            updateSegmentHandles();
        }
        if (property_name == LayerElementItem::P_HANDLE_BRUSH_COLOR) {
            updateSegmentHandles();
        }
        if (property_name == LayerElementItem::P_HANDLE_PEN_WIDTH) {
            updateSegmentHandles();
        }
        if (property_name == LayerElementItem::P_HANDLE_PEN_COLOR) {
            updateSegmentHandles();
        }

        // Roughness handles update
        if (property_name == LayerElementItem::P_R_HANDLE_RADIUS) {
            updateRoughness();
        }
        if (property_name == LayerElementItem::P_R_HANDLE_BRUSH_COLOR) {
            updateRoughness();
        }
        if (property_name == LayerElementItem::P_R_HANDLE_PEN_WIDTH) {
            updateRoughness();
        }
        if (property_name == LayerElementItem::P_R_HANDLE_PEN_COLOR) {
            updateRoughness();
        }

        // Roughness update
        if (property_name == LayerElementItem::P_ROUGHNESS_BRUSH_COLOR) {
            updateRoughness();
        }
        if (property_name == LayerElementItem::P_ROUGHNESS_PEN_WIDTH) {
            updateRoughness();
        }
        if (property_name == LayerElementItem::P_ROUGHNESS_PEN_COLOR) {
            updateRoughness();
        }
    };

    layerElementItem()->mapper()->setOnPropertyChange(on_property_change, this);
}

//! Disconnect from the set item
void LayerElementController::disconnectFormModel() const
{
    layerElementItem()->mapper()->unsubscribe(this);
}

//! Set the scene
void LayerElementController::setScene(GraphicsScene* scene)
{
    if (!scene)
        return;

    p_scene = scene;

    putSegementsOnScene();
    putSegmentHandlesOnScene();
    putRoughnessOnScene();
    putRoughnessHandlesOnScene();
}

//! Return the current set scene
GraphicsScene* LayerElementController::scene() const
{
    return p_scene;
}

//! Set the scene
void LayerElementController::unsetScene()
{
    if (!scene())
        return;

    removeSegmentsFromScene();
    removeSegmentHandlesFromScene();
    removeRoughnessFromScene();
    removeRoughnessHandlesFromScene();
    p_scene = nullptr;
}

//! Set the idenfier of the sample item to report
void LayerElementController::setSampleItemId(std::string identifier)
{
    m_sample_item_id = identifier;
}

//! Return the set sample item identifier
std::string LayerElementController::sampleItemId() const
{
    return m_sample_item_id;
}

//! Unset the sample item identifier
void LayerElementController::unsetSampleItemId()
{
    m_sample_item_id = " ";
}

//! Get the scene adapter to convert to axes
SceneAdapterInterface* LayerElementController::sceneAdapter() const
{
    if (!p_scene)
        return nullptr;

    return p_scene->sceneAdapter();
}

//! Set the layer above the current one in relation
void LayerElementController::setLayerAbove(LayerElementController* layer_view_controller)
{
    p_controller_above = layer_view_controller;

    if (layer_view_controller->layerBelow() != this)
        layer_view_controller->setLayerBelow(this);

    double pos =
        p_controller_above->layerElementItem()->property<double>(LayerElementItem::P_X_POS)
        + p_controller_above->layerElementItem()->property<double>(LayerElementItem::P_WIDTH);
    layerElementItem()->setProperty(LayerElementItem::P_X_POS, pos);
}

//! Set the layer below the current one in relation
void LayerElementController::setLayerBelow(LayerElementController* layer_view_controller)
{
    p_controller_below = layer_view_controller;

    if (layer_view_controller->layerAbove() != this)
        layer_view_controller->setLayerAbove(this);
}

//! Return the layer above the current one in relation
LayerElementController* LayerElementController::layerAbove() const
{
    return p_controller_above;
}

//! Return the layer below the current one in relation
LayerElementController* LayerElementController::layerBelow() const
{
    return p_controller_below;
}

//! Unset the layer above the current one in relation
void LayerElementController::unsetLayerAbove(bool silent)
{
    if (!p_controller_above)
        return;

    if (silent)
        p_controller_above->unsetLayerBelow(false);

    p_controller_above = nullptr;
}

//! Unset the layer below the current one in relation
void LayerElementController::unsetLayerBelow(bool silent)
{
    if (!p_controller_below)
        return;

    if (silent)
        p_controller_below->unsetLayerAbove(false);

    p_controller_below = nullptr;
}

//! Set the side segment elements
void LayerElementController::setSideSegment(SegmentElementView* segment_view)
{
    m_segment_views[0] = segment_view;
    m_segment_views[0]->adaptW(false);
    m_segment_views[0]->setLayerElementController(this);
    updateSideSegment();

    if (scene())
        scene()->addItem(m_segment_views[0]);
}

//! Set the top segment elements
void LayerElementController::setTopSegment(SegmentElementView* segment_view)
{
    m_segment_views[1] = segment_view;
    m_segment_views[1]->adaptH(false);
    m_segment_views[1]->setLayerElementController(this);
    updateTopSegment();

    if (scene())
        scene()->addItem(m_segment_views[1]);
}

//! Return the side Segment view
SegmentElementView* LayerElementController::sideSegment() const
{
    return m_segment_views[0];
}

//! Return the top Segment view
SegmentElementView* LayerElementController::topSegment() const
{
    return m_segment_views[1];
}

//! Unset the side segment elements
void LayerElementController::unsetSideSegment()
{
    if (m_segment_views[0] && scene() && m_segment_views[0]->scene() == scene())
        scene()->removeItem(m_segment_views[0]);

    m_segment_views[0] = nullptr;
}

//! Unset the top segment elements
void LayerElementController::unsetTopSegment()
{
    if (m_segment_views[1] && scene() && m_segment_views[1]->scene() == scene())
        scene()->removeItem(m_segment_views[1]);

    m_segment_views[1] = nullptr;
}

//! The move logic for the segments
void LayerElementController::segmentViewMoved(SegmentElementView* segment_view)
{
    if (segment_view == sideSegment()) {
        sideSegmentMoved();
    } else if (segment_view == topSegment()) {
        topSegmentMoved();
    }
}

//! Update the view of the side segment
void LayerElementController::updateSideSegment() const
{
    if (!m_segment_views[0])
        return;

    auto pen = QPen();
    pen.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_SIDE_PEN_COLOR));
    pen.setWidthF(layerElementItem()->property<double>(LayerElementItem::P_SIDE_PEN_WIDTH));
    m_segment_views.at(0)->setPen(pen);

    auto brush = QBrush(Qt::SolidPattern);
    brush.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_SIDE_BRUSH_COLOR));
    m_segment_views.at(0)->setBrush(brush);

    m_segment_views.at(0)->setRectangle(sideSegmentRect());
}

//! Update the view of the top segment
void LayerElementController::updateTopSegment() const
{
    if (!m_segment_views[1])
        return;

    auto pen = QPen();
    pen.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_TOP_PEN_COLOR));
    pen.setWidthF(layerElementItem()->property<double>(LayerElementItem::P_TOP_PEN_WIDTH));
    m_segment_views.at(1)->setPen(pen);

    auto brush = QBrush(Qt::SolidPattern);
    brush.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_TOP_BRUSH_COLOR));
    m_segment_views.at(1)->setBrush(brush);

    m_segment_views.at(1)->setRectangle(topSegmentRect());
}

//! Return the side segment rectangle
QRectF LayerElementController::sideSegmentRect() const
{
    double this_pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double this_height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double this_thickness =
        layerElementItem()->property<double>(LayerElementItem::P_SIDE_THICKNESS);

    double above_height = 0;
    if (layerAbove()) {
        above_height =
            layerAbove()->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    }

    if (above_height > this_height) {
        return QRectF(this_pos - this_thickness / 2., this_height, this_thickness,
                      above_height - this_height);
    } else {
        return QRectF(this_pos - this_thickness / 2., above_height, this_thickness,
                      this_height - above_height);
    }
}

//! Return the top segment rectangle
QRectF LayerElementController::topSegmentRect() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double width = layerElementItem()->property<double>(LayerElementItem::P_WIDTH);
    double thickness = layerElementItem()->property<double>(LayerElementItem::P_TOP_THICKNESS);
    return QRectF(pos, height - thickness / 2., width, thickness);
}

//! Put segments on scene
void LayerElementController::putSegementsOnScene() const
{
    if (!scene())
        return;
    for (auto segment_view : m_segment_views) {
        if (segment_view)
            scene()->addItem(segment_view);
    }
}

//! Remove the segments from the scene
void LayerElementController::removeSegmentsFromScene() const
{
    if (!scene())
        return;
    for (auto segment_view : m_segment_views) {
        if (segment_view && segment_view->scene() == scene())
            scene()->removeItem(segment_view);
    }
}

//! Handle the position variation of the side segment
void LayerElementController::sideSegmentMoved() const
{
    double x = sideSegment()->getLastPos().x();
    if (layerAbove()) {
        double w = 0;
        auto item = layerAbove()->layerElementItem();
        if (x < item->property<double>(LayerElementItem::P_X_POS)) {
            x = item->property<double>(LayerElementItem::P_X_POS) + w;
        } else {
            w = x - item->property<double>(LayerElementItem::P_X_POS);
        }
        item->setProperty(LayerElementItem::P_WIDTH, w);
    }
    layerElementItem()->setProperty(LayerElementItem::P_X_POS, x);
}

//! Handle the position variation of the top segment
void LayerElementController::topSegmentMoved() const
{
    double y = topSegment()->getLastPos().y();
    if (y < 0)
        y = 0;
    layerElementItem()->setProperty(LayerElementItem::P_HEIGHT, y);
}

//! Set the side segment elements
void LayerElementController::setSegmentHandles(HandleElementView* first_handle,
                                               HandleElementView* second_handle)
{
    m_handle_views[0] = first_handle;
    m_handle_views[1] = second_handle;
    m_handle_views[0]->setLayerElementController(this);
    m_handle_views[1]->setLayerElementController(this);
    updateSegmentHandles();

    if (scene()) {
        scene()->addItem(m_handle_views[0]);
        scene()->addItem(m_handle_views[1]);
    }
}

//! Return the side Segment view
HandleElementView* LayerElementController::firstSegmentHandle() const
{
    return m_handle_views[0];
}

//! Return the top Segment view
HandleElementView* LayerElementController::secondSegmentHandle() const
{
    return m_handle_views[1];
}

//! Unset the side segment elements
void LayerElementController::unsetSegmentHandles()
{
    if (m_handle_views[0] && scene() && m_handle_views[0]->scene() == scene())
        scene()->removeItem(m_handle_views[0]);
    if (m_handle_views[1] && scene() && m_handle_views[1]->scene() == scene())
        scene()->removeItem(m_handle_views[1]);

    m_handle_views[0] = nullptr;
    m_handle_views[1] = nullptr;
}

//! The move logic for the handles associated to the segments
void LayerElementController::handleViewMoved(HandleElementView* handle_view)
{
    if (handle_view == leftRoughnessHandle()) {
        leftHandleMoved();
    } else if (handle_view == rightRoughnessHandle()) {
        rightHandleMoved();
    }
}

//! Update the handles of the segment
void LayerElementController::updateSegmentHandles() const
{
    auto pen = QPen();
    pen.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_HANDLE_PEN_COLOR));
    pen.setWidthF(layerElementItem()->property<double>(LayerElementItem::P_HANDLE_PEN_WIDTH));

    auto brush = QBrush(Qt::SolidPattern);
    brush.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_HANDLE_BRUSH_COLOR));

    if (m_handle_views[0]) {
        m_handle_views.at(0)->setPen(pen);
        m_handle_views.at(0)->setBrush(brush);
        m_handle_views.at(0)->setRectangle(firstSegmentHandleRect());
    }
    if (m_handle_views[1]) {
        m_handle_views.at(1)->setPen(pen);
        m_handle_views.at(1)->setBrush(brush);
        m_handle_views.at(1)->setRectangle(secondSegmentHandleRect());
    }
}

//! Get the first segment handle rectangle
QRectF LayerElementController::firstSegmentHandleRect() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double radius = layerElementItem()->property<double>(LayerElementItem::P_HANDLE_RADIUS);

    double above_height = 0;
    if (layerAbove()) {
        above_height =
            layerAbove()->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    }

    return QRectF(pos - radius, above_height - radius, 2 * radius, 2 * radius);
}

//! Get the second segment handle rectangle
QRectF LayerElementController::secondSegmentHandleRect() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double radius = layerElementItem()->property<double>(LayerElementItem::P_HANDLE_RADIUS);
    return QRectF(pos - radius, height - radius, 2 * radius, 2 * radius);
}

//! Put the segment handles on the secene
void LayerElementController::putSegmentHandlesOnScene() const
{
    if (!scene())
        return;
    for (auto handle_view : m_handle_views) {
        if (handle_view)
            scene()->addItem(handle_view);
    }
}

//! Remove the segment handles on the scene
void LayerElementController::removeSegmentHandlesFromScene() const
{
    if (!scene())
        return;
    for (auto handle_view : m_handle_views) {
        if (handle_view && handle_view->scene() == scene())
            scene()->removeItem(handle_view);
    }
}

//! Set the roughness element view
void LayerElementController::setRoughness(RoughnessElementView* roughness_view)
{
    p_roughness_view = roughness_view;
    updateRoughness();

    if (scene()) {
        scene()->addItem(p_roughness_view);
    }
}

//! Set the roughness handle element views
void LayerElementController::setRoughnessHandles(HandleElementView* first_handle_view,
                                                 HandleElementView* second_handle_view)
{
    m_rough_handles_views[0] = first_handle_view;
    m_rough_handles_views[1] = second_handle_view;
    m_rough_handles_views[0]->setFlag(QGraphicsItem::ItemIsMovable);
    m_rough_handles_views[1]->setFlag(QGraphicsItem::ItemIsMovable);
    m_rough_handles_views[0]->setLayerElementController(this);
    m_rough_handles_views[1]->setLayerElementController(this);
    updateRoughness();

    if (scene()) {
        scene()->addItem(m_rough_handles_views[0]);
        scene()->addItem(m_rough_handles_views[1]);
    }
}

//! Return the roughness element view
RoughnessElementView* LayerElementController::roughness() const
{
    return p_roughness_view;
}

//! Return the left roughness handle element view
HandleElementView* LayerElementController::leftRoughnessHandle() const
{
    return m_rough_handles_views[0];
}

//! Return the right roughness handle element view
HandleElementView* LayerElementController::rightRoughnessHandle() const
{
    return m_rough_handles_views[1];
}

//! Remove the roughness view element pointer
void LayerElementController::unsetRoughness()
{
    if (p_roughness_view && scene() && p_roughness_view->scene() == scene())
        scene()->removeItem(p_roughness_view);
    p_roughness_view = nullptr;
}

//! Remove the handle pointers
void LayerElementController::unsetRoughnessHandles()
{
    if (m_rough_handles_views[0] && scene() && m_rough_handles_views[0]->scene() == scene())
        scene()->removeItem(m_rough_handles_views[0]);
    if (m_rough_handles_views[1] && scene() && m_rough_handles_views[1]->scene() == scene())
        scene()->removeItem(m_rough_handles_views[1]);

    m_rough_handles_views[0] = nullptr;
    m_rough_handles_views[1] = nullptr;
}

//! Update the whole roughness drawing
void LayerElementController::updateRoughness() const
{
    // Test the roughness
    double roughness = layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS);
    double width = layerElementItem()->property<double>(LayerElementItem::P_WIDTH);
    setRoughnessInLimits(roughness, false);

    // Perform the painting
    auto pen = QPen();
    auto brush = QBrush();

    // Take care of the rounghnessview
    pen.setStyle(Qt::PenStyle::DashLine);
    pen.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_ROUGHNESS_PEN_COLOR));
    pen.setWidthF(layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS_PEN_WIDTH));
    brush.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_ROUGHNESS_BRUSH_COLOR));
    if (p_roughness_view) {
        p_roughness_view->setPen(pen);
        p_roughness_view->setBrush(brush);
        p_roughness_view->setLeftPath(leftRoughnessPath());
        p_roughness_view->setRightPath(rightRoughnessPath());
    }

    // Take care of the handles
    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_R_HANDLE_PEN_COLOR));
    pen.setWidthF(layerElementItem()->property<double>(LayerElementItem::P_R_HANDLE_PEN_WIDTH));
    brush.setColor(layerElementItem()->property<QColor>(LayerElementItem::P_R_HANDLE_BRUSH_COLOR));
    brush.setStyle(Qt::SolidPattern);

    if (m_rough_handles_views[0]) {
        m_rough_handles_views.at(0)->setPen(pen);
        m_rough_handles_views.at(0)->setBrush(brush);
        m_rough_handles_views.at(0)->setRectangle(leftRoughnessHandleRect());
    }
    if (m_rough_handles_views[1]) {
        m_rough_handles_views.at(1)->setPen(pen);
        m_rough_handles_views.at(1)->setBrush(brush);
        m_rough_handles_views.at(1)->setRectangle(rightRoughnessHandleRect());
    }
}

//! get the left painter path for the roughness view
QPainterPath LayerElementController::leftRoughnessPath() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double roughness = layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS);

    auto path = QPainterPath();

    auto layer_above = layerAbove();
    if (!layer_above) {
        path.moveTo(pos, 0);
        path.lineTo(pos - roughness, 0);
    } else {
        path.moveTo(pos - roughness,
                    layer_above->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT));
    }
    path.lineTo(pos - roughness, height);
    path.lineTo(pos, height);

    return path;
}

//! get the right painter path for the roughness view
QPainterPath LayerElementController::rightRoughnessPath() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double roughness = layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS);

    auto path = QPainterPath();

    auto layer_above = layerAbove();
    if (!layer_above) {
        path.moveTo(pos, 0);
        path.lineTo(pos + roughness, 0);
    } else {
        path.moveTo(pos,
                    layer_above->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT));
        path.lineTo(pos + roughness,
                    layer_above->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT));
    }
    path.lineTo(pos + roughness, height);

    return path;
}

//! get the rectangle for the left roughness handles
QRectF LayerElementController::leftRoughnessHandleRect() const
{
    double pos_x = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double radius = layerElementItem()->property<double>(LayerElementItem::P_R_HANDLE_RADIUS);
    double roughness = layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS);

    auto layer_above = layerAbove();
    double lower_height = 0;
    if (layer_above) {
        lower_height =
            layer_above->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    }
    double pos_y = (lower_height - height) / 2 + height;

    return QRectF(pos_x - roughness - radius, pos_y - radius, 2 * radius, 2 * radius);
}

//! get the rectangle for the right roughness handles
QRectF LayerElementController::rightRoughnessHandleRect() const
{
    double pos_x = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double height = layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    double radius = layerElementItem()->property<double>(LayerElementItem::P_R_HANDLE_RADIUS);
    double roughness = layerElementItem()->property<double>(LayerElementItem::P_ROUGHNESS);

    auto layer_above = layerAbove();
    double lower_height = 0;
    if (layer_above) {
        lower_height =
            layer_above->layerElementItem()->property<double>(LayerElementItem::P_HEIGHT);
    }
    double pos_y = (lower_height - height) / 2 + height;

    return QRectF(pos_x + roughness - radius, pos_y - radius, 2 * radius, 2 * radius);
}

//! Put the roughnes view on the scene
void LayerElementController::putRoughnessOnScene() const
{
    if (!scene())
        return;
    if (p_roughness_view)
        scene()->addItem(p_roughness_view);
}

//! Put the roughness handles on the scene
void LayerElementController::putRoughnessHandlesOnScene() const
{
    if (!scene())
        return;
    for (auto handle_roughness_view : m_rough_handles_views) {
        if (handle_roughness_view)
            scene()->addItem(handle_roughness_view);
    }
}

//! Remove the roughness view item from the scene
void LayerElementController::removeRoughnessFromScene() const
{
    if (!scene())
        return;
    if (p_roughness_view && p_roughness_view->scene() == scene())
        scene()->removeItem(p_roughness_view);
}

//! Remove the roughness handles from the sene
void LayerElementController::removeRoughnessHandlesFromScene() const
{
    if (!scene())
        return;
    for (auto handle_roughness_view : m_rough_handles_views) {
        if (handle_roughness_view && handle_roughness_view->scene() == scene())
            scene()->removeItem(handle_roughness_view);
    }
}

//! Handle the position variation of the left handle
void LayerElementController::leftHandleMoved() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double roughness = pos - leftRoughnessHandle()->getLastPos().x();
    setRoughnessInLimits(roughness);
}

//! Handle the position variation of the right handle
void LayerElementController::rightHandleMoved() const
{
    double pos = layerElementItem()->property<double>(LayerElementItem::P_X_POS);
    double roughness = rightRoughnessHandle()->getLastPos().x() - pos;
    setRoughnessInLimits(roughness);
}

//! Handle the position variation of the right handle
void LayerElementController::setRoughnessInLimits(double roughness, bool active) const
{
    if (roughness < 0) {
        layerElementItem()->setProperty(LayerElementItem::P_ROUGHNESS, 0.);
        return;
    }

    double width = layerElementItem()->property<double>(LayerElementItem::P_WIDTH);
    if (width == 0)
        width = 1e6;

    auto layer_above = layerAbove();
    if (layer_above) {
        double second_width =
            layer_above->layerElementItem()->property<double>(LayerElementItem::P_WIDTH);
        if (second_width == 0)
            second_width = 1e6;

        if (second_width < width)
            width = second_width;
    }

    if (roughness > width / 2.) {
        layerElementItem()->setProperty(LayerElementItem::P_ROUGHNESS, width / 2.);
        return;
    }

    if (active)
        layerElementItem()->setProperty(LayerElementItem::P_ROUGHNESS, roughness);
}

} // namespace DaRefl
