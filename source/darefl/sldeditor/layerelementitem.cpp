// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementitem.h>

#include <mvvm/factories/modeldocuments.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

namespace DaRefl
{

LayerElementItem::LayerElementItem() : ModelView::CompoundItem("LayerElement")
{
    addProperty(P_X_POS, 0.)->setDisplayName("Position");
    addProperty(P_WIDTH, 10.)->setDisplayName("Width");
    addProperty(P_HEIGHT, 10.)->setDisplayName("Height");
    addProperty(P_ROUGHNESS, 5.)->setDisplayName("Roughness");

    addProperty(P_SIDE_THICKNESS, 5.)->setDisplayName("Side segment thickness");
    addProperty(P_SIDE_BRUSH_COLOR, QColor("black"))->setDisplayName("Side segment color");
    addProperty(P_SIDE_PEN_WIDTH, 2.)->setDisplayName("Side segment pen width");
    addProperty(P_SIDE_PEN_COLOR, QColor("black"))->setDisplayName("Side segment pen color");

    addProperty(P_TOP_THICKNESS, 5.)->setDisplayName("Top segment thickness");
    addProperty(P_TOP_BRUSH_COLOR, QColor("black"))->setDisplayName("Top segment color");
    addProperty(P_TOP_PEN_WIDTH, 2.)->setDisplayName("Top segment pen width");
    addProperty(P_TOP_PEN_COLOR, QColor("black"))->setDisplayName("Top segment pen color");

    addProperty(P_HANDLE_RADIUS, 5.)->setDisplayName("Handle radius");
    addProperty(P_HANDLE_BRUSH_COLOR, QColor("black"))->setDisplayName("Handle color");
    addProperty(P_HANDLE_PEN_WIDTH, 2.)->setDisplayName("Handle pen width");
    addProperty(P_HANDLE_PEN_COLOR, QColor("black"))->setDisplayName("Handle pen color");

    addProperty(P_R_HANDLE_RADIUS, 4.)->setDisplayName("Roughness handle radius");
    addProperty(P_R_HANDLE_BRUSH_COLOR, QColor("black"))->setDisplayName("Roughness handle color");
    addProperty(P_R_HANDLE_PEN_WIDTH, 2.)->setDisplayName("Roughness handle pen width");
    addProperty(P_R_HANDLE_PEN_COLOR, QColor("black"))
        ->setDisplayName("Roughness handle pen color");

    addProperty(P_ROUGHNESS_BRUSH_COLOR, QColor("black"))->setDisplayName("Roughness handle color");
    addProperty(P_ROUGHNESS_PEN_WIDTH, 2.)->setDisplayName("Roughness handle pen width");
    addProperty(P_ROUGHNESS_PEN_COLOR, QColor("black"))
        ->setDisplayName("Roughness handle pen color");
}

} // namespace DaRefl
