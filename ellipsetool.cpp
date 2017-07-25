/*
Copyright 2017 SillyLossy.
This program is free software; you can redistribute it and/or
modify it under the terms of the Lesser GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the Lesser GNU General Public License for more details.
You should have received a copy of the Lesser GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ellipsetool.h"
#include <QPainter>

const QString EllipseTool::toolName()
{
    static const QString ellipseName = QStringLiteral("Ellipse");
    return ellipseName;
}

const QString EllipseTool::iconName()
{
    static const QString ellipseIcon = QStringLiteral("ellipse");
    return ellipseIcon;
}

void EllipseTool::paint(PaintEvent* event, bool temporary)
{
    clearToolLayer(event->toolLayer);
    QPaintDevice* device;
    if (temporary) {
        device = event->toolLayer;
    }
    else {
        device = event->selectedLayer;
    }
    QPainter painter(device);
    if (event->antialiasingEnabled)
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(event->pen);
    painter.setBrush(event->brush);
    painter.drawEllipse(QRectF(m_originPoint, event->currentPoint));
}



void EllipseTool::onMouseMove(PaintEvent* event)
{
    if (event->currentPoint.x() == m_originPoint.x() || event->currentPoint.y() == m_originPoint.y()) {
        return;
    }
    paint(event, true);
}

void EllipseTool::onMouseRelease(PaintEvent* event)
{
    if (event->currentPoint.x() == m_originPoint.x() || event->currentPoint.y() == m_originPoint.y()) {
        return;
    }
    paint(event, false);
    clearToolLayer(event->toolLayer);
}
