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

#include "rectangletool.h"
#include <QPainter>

const QString RectangleTool::toolName()
{
    static const QString rectangleName = QStringLiteral("Rectangle");
    return rectangleName;
}

const QString RectangleTool::iconName()
{
    static const QString rectangleIcon = QStringLiteral("rectangle");
    return rectangleIcon;
}

void RectangleTool::paint(PaintEvent *event, bool temporary)
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
    painter.drawRect(QRect(m_originPoint, event->currentPoint));
}

void RectangleTool::onMouseMove(PaintEvent* event)
{
    if (event->currentPoint.x() == m_originPoint.x() || event->currentPoint.y() == m_originPoint.y()) {
        return;
    }
    paint(event, true);
}

void RectangleTool::onMouseRelease(PaintEvent* event)
{
    if (event->currentPoint.x() == m_originPoint.x() || event->currentPoint.y() == m_originPoint.y()) {
        return;
    }
    paint(event, false);
    clearToolLayer(event->toolLayer);
}
