// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDELEMENTCONTROLLER_H
#define DAREFL_SLDEDITOR_SLDELEMENTCONTROLLER_H

#include <QObject>
#include <darefl/sldeditor/layerelementcontroller.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <vector>

class MaterialModel;
class SampleModel;
class SLDElementModel;
class GraphicsScene;

//! The controller of the sld layer visual representation
class SLDElementController : public QObject
{
    Q_OBJECT

public:
    using string_vec = std::vector<std::string>;
    using layer_ctrl_vec = std::vector<std::unique_ptr<LayerElementController>>;

    SLDElementController(MaterialModel* material_model, SampleModel* sample_model,
                         SLDElementModel* sld_model, GraphicsScene* scene_item);
    ~SLDElementController();
    void setScene(GraphicsScene* scene);

private:
    void connectMaterialModel();
    void connectLayerModel();
    void connectSLDElementModel();
    void disconnectMaterialModel() const;
    void disconnectLayerModel() const;
    void disconnectSLDElementModel() const;

    void buildSLD();
    void clearScene();
    string_vec getIdentifierVector(ModelView::SessionItem* item);
    void buildLayerControllers(string_vec& identifiers);
    void connectLayerControllers();
    void disconnectLayerControllers();

    void updateToView(ModelView::SessionItem* item = nullptr);
    void updateThicknessFromView(std::string identifier, double value);
    void updateSLDFromView(std::string identifier, double value);
    void updateRoughnessFromView(std::string identifier, double value);

private:
    MaterialModel* p_material_model;
    SampleModel* p_sample_model;
    SLDElementModel* p_sld_model;
    GraphicsScene* p_scene_item;
    layer_ctrl_vec m_layer_controllers;
};

#endif // DAREFL_SLDEDITOR_SLDELEMENTCONTROLLER_H
