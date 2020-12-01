// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementcontroller.h>
#include <darefl/sldeditor/roughnesselementview.h>

#include <QPainter>
#include <QStyleOption>

namespace DaRefl
{

//! The constructor
RoughnessElementView::RoughnessElementView()
    : ElementView()
    , m_left_path(QPainterPath())
    , m_right_path(QPainterPath())
    , m_brush(QBrush())
    , m_pen(QPen())
{
    setZValue(0);
}

//! The overriden paint method
void RoughnessElementView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setClipRect(sceneAdapter()->viewportRectangle());
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(displayPath(m_left_path));
    painter->drawPath(displayPath(m_right_path));
}

//! The shape
QPainterPath RoughnessElementView::shape() const
{
    QPainterPath path;
    path.addPath(displayPath(m_left_path));
    path.addPath(displayPath(m_right_path));
    return path;
}

//! The bounding rectangle of the handle
QRectF RoughnessElementView::boundingRect() const
{
    QPainterPath path;
    path.addPath(displayPath(m_left_path));
    path.addPath(displayPath(m_right_path));
    return path.boundingRect();
}

//! Set the draw path for the left side
void RoughnessElementView::setLeftPath(QPainterPath left_path)
{
    prepareGeometryChange();
    m_left_path = left_path;
}

//! Set the draw path for the right side
void RoughnessElementView::setRightPath(QPainterPath right_path)
{
    prepareGeometryChange();
    m_right_path = right_path;
}

//! Set the brush
void RoughnessElementView::setBrush(QBrush brush)
{
    m_brush = brush;
}

//! Set the pen
void RoughnessElementView::setPen(QPen pen)
{
    m_pen = pen;
}

} // namespace DaRefl
