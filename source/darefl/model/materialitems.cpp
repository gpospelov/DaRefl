// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <darefl/model/item_constants.h>
#include <darefl/model/materialitems.h>
#include <mvvm/model/externalproperty.h>

using namespace ModelView;

namespace DaRefl
{

MaterialContainerItem::MaterialContainerItem()
    : ModelView::CompoundItem(Constants::MaterialContainerItemType)
{
    registerTag(TagInfo::universalTag(T_MATERIALS, {Constants::SLDMaterialItemType}),
                /*set_as_default*/ true);
}

// ----------------------------------------------------------------------------

MaterialBaseItem::MaterialBaseItem(const std::string& model_type)
    : ModelView::CompoundItem(model_type)
{
    addProperty(P_COLOR, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
}

//! Returns ExternalProperty representing this material.

ModelView::ExternalProperty MaterialBaseItem::external_property() const
{
    QColor color = isTag(P_COLOR) ? property<QColor>(P_COLOR) : QColor(Qt::red);
    std::string name = isTag(P_NAME) ? property<std::string>(P_NAME) : std::string();
    return ModelView::ExternalProperty(name, color, identifier());
}

/*! Creates mag. field-related properties.
 *  Should be called from descendants' constructors in order
 *  to preserve view-oriented property sequence.
 *  The same can be achieved with a proper
 *  ModelView::RowStrategyInterface::constructRow
 *  implementation.
 */
void MaterialBaseItem::init_magnetic_field()
{
    addProperty(P_H_X, 0.0)->setDisplayName("H, x");
    addProperty(P_H_Y, 0.0)->setDisplayName("H, y");
    addProperty(P_H_Z, 0.0)->setDisplayName("H, z");
}

// ----------------------------------------------------------------------------

SLDMaterialItem::SLDMaterialItem() : MaterialBaseItem(Constants::SLDMaterialItemType)
{
    addProperty(P_SLD_REAL, 1e-06)->setDisplayName("Re(SLD)")->setLimits(RealLimits::limitless());
    addProperty(P_SLD_IMAG, 1e-08)->setDisplayName("Im(SLD)")->setLimits(RealLimits::limitless());
    init_magnetic_field();
}

void SLDMaterialItem::set_properties(const std::string& name, const QColor& color, double real,
                                     double imag)
{
    setProperty(P_NAME, name);
    setProperty(P_COLOR, color);
    setProperty(P_SLD_REAL, real);
    setProperty(P_SLD_IMAG, imag);
}

} // namespace DaRefl
