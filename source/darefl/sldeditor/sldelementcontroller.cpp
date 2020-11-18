// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/sampleitems.h>
#include <darefl/model/materialitems.h>
#include <darefl/model/materialmodel.h>
#include <darefl/model/samplemodel.h>
#include <darefl/sldeditor/graphicsscene.h>
#include <darefl/sldeditor/segmentelementview.h>
#include <darefl/sldeditor/sldelementcontroller.h>

#include <darefl/sldeditor/layerelementcontroller.h>
#include <darefl/sldeditor/layerelementitem.h>
#include <darefl/sldeditor/sldelementmodel.h>

#include <mvvm/model/compounditem.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>
#include <mvvm/signals/modelmapper.h>

#include <iostream>

using namespace ModelView;

//! Contructor
SLDElementController::SLDElementController(MaterialModel* material_model, SampleModel* sample_model,
                                           SLDElementModel* sld_model, GraphicsScene* scene_item)
    : p_material_model(material_model)
    , p_sample_model(sample_model)
    , p_sld_model(sld_model)
    , p_scene_item(scene_item)
{
    connectSLDElementModel();
    connectLayerModel();
    connectMaterialModel();
    buildSLD();
}

SLDElementController::~SLDElementController()
{
    clearScene();
}

//! Connect with signals of MaterialModel
void SLDElementController::connectMaterialModel()
{
    auto on_mat_data_change = [this](SessionItem* item, int) { updateToView(item); };
    p_material_model->mapper()->setOnDataChange(on_mat_data_change, this);

    auto on_mat_model_destroyed = [this](SessionModel*) { p_material_model = nullptr; };
    p_material_model->mapper()->setOnModelDestroyed(on_mat_model_destroyed, this);
}

// FIXME Consider switching to ModelHasChangedController, or ModelListener.
// See quicksimcontroller.h or materialpropertycontroller.h as an example.

//! Connect with signals of SampleModel
void SLDElementController::connectLayerModel()
{
    auto on_sam_data_change = [this](SessionItem* item, int) { updateToView(item); };
    p_sample_model->mapper()->setOnDataChange(on_sam_data_change, this);

    auto on_sam_item_inserted = [this](SessionItem*, TagRow) { buildSLD(); };
    p_sample_model->mapper()->setOnItemInserted(on_sam_item_inserted, this);

    auto on_sam_item_removed = [this](SessionItem*, TagRow) { buildSLD(); };
    p_sample_model->mapper()->setOnItemRemoved(on_sam_item_removed, this);

    auto on_sam_model_destroyed = [this](SessionModel*) { p_sample_model = nullptr; };
    p_sample_model->mapper()->setOnModelDestroyed(on_sam_model_destroyed, this);
}

//! Connect with signals of SLDViewModel
void SLDElementController::connectSLDElementModel()
{
    auto on_sld_model_destroyed = [this](SessionModel*) { p_sld_model = nullptr; };
    p_sld_model->mapper()->setOnModelDestroyed(on_sld_model_destroyed, this);
}

//! Disconnect with signals of MaterialModel
void SLDElementController::disconnectMaterialModel() const
{
    p_material_model->mapper()->unsubscribe(this);
}

//! Disconnect with signals of SampleModel
void SLDElementController::disconnectLayerModel() const
{
    p_sample_model->mapper()->unsubscribe(this);
}

//! Disconnect with signals of SLDViewModel
void SLDElementController::disconnectSLDElementModel() const
{
    p_sld_model->mapper()->unsubscribe(this);
}

//! Set the scene of the current controller to be passed to the LayerElementControllers
void SLDElementController::setScene(GraphicsScene* scene)
{
    p_scene_item = scene;
    buildSLD();
}

//! Updates all material properties in LayerItems to get new material colors and labels
void SLDElementController::buildSLD()
{
    if (!p_sld_model)
        return;
    if (!p_sample_model)
        return;
    if (!p_material_model)
        return;
    if (!p_scene_item)
        return;

    disconnectSLDElementModel();
    clearScene();

    if (p_sample_model->rootItem()->childrenCount() == 0)
        return;
    string_vec identifiers = getIdentifierVector(p_sample_model->rootItem()->children().at(0));
    if (identifiers.size() == 0)
        return;

    buildLayerControllers(identifiers);
    updateToView();
    connectSLDElementModel();
    connectLayerControllers();
}

//! Remove all LayerElementControllers and their items from scene and memory
void SLDElementController::clearScene()
{
    if (!p_scene_item)
        return;
    if (!p_sld_model)
        return;

    for (int i = 0; i < m_layer_controllers.size(); ++i) {
        m_layer_controllers.at(i)->disconnectFormModel();
        m_layer_controllers.at(i)->unsetScene();
        m_layer_controllers.at(i)->deleteViewItems();
    }
    m_layer_controllers.clear();
    p_sld_model->clear();
}

//! Get the identifiers of all layeritems in the sample model in order of appearance
SLDElementController::string_vec SLDElementController::getIdentifierVector(SessionItem* item)
{
    string_vec output;

    auto children = item->children();
    for (int i = 0; i < item->childrenCount(); ++i) {
        if (dynamic_cast<MultiLayerItem*>(children.at(i))) {
            auto child = dynamic_cast<MultiLayerItem*>(children.at(i));
            for (int j = 0; j < child->property<int>(MultiLayerItem::P_NREPETITIONS); ++j) {
                auto child_output = getIdentifierVector(child);
                output.insert(output.end(), child_output.begin(), child_output.end());
            }
        } else if (dynamic_cast<LayerItem*>(children.at(i))) {
            auto child = dynamic_cast<LayerItem*>(children.at(i));
            output.push_back(child->identifier());
        }
    }
    return output;
}

//! Build and set up the layer controllers
void SLDElementController::buildLayerControllers(string_vec& identifiers)
{
    if (!p_scene_item)
        return;
    if (!p_sld_model)
        return;

    for (auto& identifier : identifiers) {
        auto layer_element_item = p_sld_model->addLayer();
        auto layer_element_controller =
            std::make_unique<LayerElementController>(layer_element_item);
        layer_element_controller->autoPopulate();
        layer_element_controller->setScene(p_scene_item);
        layer_element_controller->connectToModel();
        layer_element_controller->setSampleItemId(identifier);
        m_layer_controllers.push_back(std::move(layer_element_controller));
    }

    for (int i = 0; i < m_layer_controllers.size() - 1; ++i) {
        m_layer_controllers.at(i)->setLayerBelow(m_layer_controllers.at(i + 1).get());
    }

    if (m_layer_controllers.size() > 0) {
        m_layer_controllers.at(0)->topSegment()->stretchRight(true);
        m_layer_controllers.at(0)->topSegment()->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    if (m_layer_controllers.size() > 1) {
        m_layer_controllers.at(1)->sideSegment()->setFlag(QGraphicsItem::ItemIsMovable, false);
        m_layer_controllers.at(m_layer_controllers.size() - 1)->topSegment()->stretchLeft(true);
    }
}

//! Connect the layer controllers
void SLDElementController::connectLayerControllers()
{
    for (const auto& layer_controller : m_layer_controllers) {
        QObject::connect(layer_controller.get(), &LayerElementController::heightChanged, this,
                         &SLDElementController::updateSLDFromView);
        QObject::connect(layer_controller.get(), &LayerElementController::widthChanged, this,
                         &SLDElementController::updateThicknessFromView);
        QObject::connect(layer_controller.get(), &LayerElementController::roughnessChanged, this,
                         &SLDElementController::updateRoughnessFromView);
    }
}

//! Disconnect the layer controllers
void SLDElementController::disconnectLayerControllers()
{
    for (const auto& layer_controller : m_layer_controllers) {
        QObject::disconnect(layer_controller.get(), &LayerElementController::heightChanged, this,
                            &SLDElementController::updateSLDFromView);
        QObject::disconnect(layer_controller.get(), &LayerElementController::widthChanged, this,
                            &SLDElementController::updateThicknessFromView);
        QObject::disconnect(layer_controller.get(), &LayerElementController::roughnessChanged, this,
                            &SLDElementController::updateRoughnessFromView);
    }
}

//! Update the view items with the changes in the material or layer models
void SLDElementController::updateToView(SessionItem* item)
{
    if (item && dynamic_cast<MultiLayerItem*>(item->parent())) {
        buildSLD();
        return;
    }

    for (const auto& layer_controller : m_layer_controllers) {
        auto layer_item =
            dynamic_cast<LayerItem*>(p_sample_model->findItem(layer_controller->sampleItemId()));
        if (!layer_item) {
            buildSLD();
            return;
        }
        auto roughness_item = layer_item->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
        auto material_item = dynamic_cast<SLDMaterialItem*>(p_material_model->findItem(
            layer_item->property<ExternalProperty>(LayerItem::P_MATERIAL).identifier()));

        layer_controller->layerElementItem()->setProperty(
            LayerElementItem::P_ROUGHNESS,
            roughness_item->property<double>(RoughnessItem::P_SIGMA));
        layer_controller->layerElementItem()->setProperty(
            LayerElementItem::P_WIDTH, layer_item->property<double>(LayerItem::P_THICKNESS));

        if (material_item) {
            layer_controller->layerElementItem()->setProperty(
                LayerElementItem::P_HEIGHT,
                material_item->property<double>(SLDMaterialItem::P_SLD_REAL));
            layer_controller->layerElementItem()->setProperty(
                LayerElementItem::P_TOP_BRUSH_COLOR,
                material_item->property<QColor>(SLDMaterialItem::P_COLOR));
            layer_controller->layerElementItem()->setProperty(
                LayerElementItem::P_SIDE_BRUSH_COLOR,
                material_item->property<QColor>(SLDMaterialItem::P_COLOR));
        } else {
            layer_controller->layerElementItem()->setProperty(LayerElementItem::P_HEIGHT, 1e-6);
            layer_controller->layerElementItem()->setProperty(LayerElementItem::P_TOP_BRUSH_COLOR,
                                                              QColor("red"));
            layer_controller->layerElementItem()->setProperty(LayerElementItem::P_SIDE_BRUSH_COLOR,
                                                              QColor("red"));
        }
    }
}

//! Update the material and layer models from the view items
void SLDElementController::updateThicknessFromView(std::string identifier, double value)
{
    auto layer_item = dynamic_cast<LayerItem*>(p_sample_model->findItem(identifier));
    layer_item->setProperty(LayerItem::P_THICKNESS, value);
}

//! Update the material and layer models from the view items
void SLDElementController::updateSLDFromView(std::string identifier, double value)
{
    auto layer_item = dynamic_cast<LayerItem*>(p_sample_model->findItem(identifier));
    auto material_item = dynamic_cast<SLDMaterialItem*>(p_material_model->findItem(
        layer_item->property<ExternalProperty>(LayerItem::P_MATERIAL).identifier()));
    if (material_item)
        material_item->setProperty(SLDMaterialItem::P_SLD_REAL, value);
}

//! Update the material and layer models from the view items
void SLDElementController::updateRoughnessFromView(std::string identifier, double value)
{
    auto layer_item = dynamic_cast<LayerItem*>(p_sample_model->findItem(identifier));
    auto roughness_item = layer_item->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
    roughness_item->setProperty(RoughnessItem::P_SIGMA, value);
}
