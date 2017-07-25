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
#include "paintarea.h"
#include <QPainter>

RectangleTool::RectangleTool(PaintArea* area) : LineTool(area)
{

}

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

void RectangleTool::paint(const QPoint& p, bool temporary)
{
    clearToolLayer();
    QPaintDevice* device;
    if (temporary) {
        device = m_area->toolLayer();
    }
    else {
        device = m_area->selectedLayer();
    }
    QPainter painter(device);
    if (m_area->antialiasingEnabled())
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(m_area->pen());
    painter.setBrush(m_area->brush());
    painter.drawRect(QRect(m_originPoint, p));
}

void RectangleTool::onMouseMove(const QPoint& p)
{
    if (p.x() == m_originPoint.x() || p.y() == m_originPoint.y()) {
        return;
    }
    paint(p, true);
}

void RectangleTool::onMouseRelease(const QPoint& p)
{
    if (p.x() == m_originPoint.x() || p.y() == m_originPoint.y()) {
        return;
    }
    paint(p, false);
    clearToolLayer();
}
