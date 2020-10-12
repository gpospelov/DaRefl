// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

/*
 * This is nearly complete Material design Switch widget implementation in qtwidgets module.
 * More info: https://material.io/design/components/selection-controls.html#switches
 * Copyright (C) 2018 Iman Ahmadvand
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef STYLE_H
#define STYLE_H

#include <QColor>
#include <QFont>
#include <QMargins>
#include <QPainter>
#include <QtCore/qeasingcurve.h>

#define STYLE_cyan500 QColor("#00bcd4")
#define STYLE_gray50 QColor("#fafafa")
#define STYLE_black QColor("#000000")
#define STYLE_gray400 QColor("#bdbdbd")

Q_DECL_IMPORT void qt_blurImage(QPainter* p, QImage& blurImage, qreal radius, bool quality,
                                bool alphaOnly,
                                int transposed = 0); // src/widgets/effects/qpixmapfilter.cpp

namespace SwitchStyle
{

using Type = QEasingCurve::Type;

struct Animation {
    Animation() = default;
    Animation(Type _easing, int _duration) : easing{_easing}, duration{_duration} {}

    Type easing;
    int duration;
};

struct Switch {
    Switch()
        : height{36}, font{QFont("Roboto medium", 13)}, indicatorMargin{QMargins(8, 8, 8, 8)},
          thumbOnBrush{STYLE_cyan500}, thumbOnOpacity{1}, trackOnBrush{STYLE_cyan500},
          trackOnOpacity{0.5}, thumbOffBrush{STYLE_gray50}, thumbOffOpacity{1},
          trackOffBrush{STYLE_black}, trackOffOpacity{0.38}, thumbDisabled{STYLE_gray400},
          thumbDisabledOpacity{1}, trackDisabled{STYLE_black},
          trackDisabledOpacity{0.12}, textColor{STYLE_black}, disabledTextOpacity{0.26},
          thumbBrushAnimation{Animation(Type::Linear, 150)},
          trackBrushAnimation{Animation(Type::Linear, 150)}, thumbPosAniamtion{
                                                                 Animation(Type::InOutQuad, 150)}
    {
    }

    int height;
    QFont font;
    QMargins indicatorMargin;
    QColor thumbOnBrush;
    double thumbOnOpacity;
    QColor trackOnBrush;
    double trackOnOpacity;
    QColor thumbOffBrush;
    double thumbOffOpacity;
    QColor trackOffBrush;
    double trackOffOpacity;
    QColor thumbDisabled;
    double thumbDisabledOpacity;
    QColor trackDisabled;
    double trackDisabledOpacity;
    QColor textColor;
    double disabledTextOpacity;
    Animation thumbBrushAnimation;
    Animation trackBrushAnimation;
    Animation thumbPosAniamtion;
};

inline QPixmap drawShadowEllipse(qreal radius, qreal elevation, const QColor& color)
{
    auto px = QPixmap(radius * 2, radius * 2);
    px.fill(Qt::transparent);

    { // draw ellipes
        QPainter p(&px);
        p.setBrush(color);
        p.setPen(Qt::NoPen);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawEllipse(QRectF(0, 0, px.size().width(), px.size().height()).center(),
                      radius - elevation, radius - elevation);
    }

    QImage tmp(px.size(), QImage::Format_ARGB32_Premultiplied);
    tmp.setDevicePixelRatio(px.devicePixelRatioF());
    tmp.fill(0);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawPixmap(QPointF(), px);
    tmpPainter.end();

    // blur the alpha channel
    QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.setDevicePixelRatio(px.devicePixelRatioF());
    blurred.fill(0);
    {
        QPainter blurPainter(&blurred);
        qt_blurImage(&blurPainter, tmp, elevation * 4., true, false);
    }

    tmp = blurred;

    return QPixmap::fromImage(tmp);
}

} // namespace SwitchStyle

#endif // STYLE_H
