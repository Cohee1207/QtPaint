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
#include "paintarea.h"
#include <QPainter>

EllipseTool::EllipseTool(PaintArea* area) : LineTool(area)
{

}

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

void EllipseTool::paint(const QPoint& p, bool temporary)
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
    painter.drawEllipse(QRectF(m_originPoint, p));
}



void EllipseTool::onMouseMove(const QPoint& p)
{
    if (p.x() == m_originPoint.x() || p.y() == m_originPoint.y()) {
        return;
    }
    paint(p, true);
}

void EllipseTool::onMouseRelease(const QPoint& p)
{
    if (p.x() == m_originPoint.x() || p.y() == m_originPoint.y()) {
        return;
    }
    paint(p, false);
    clearToolLayer();
}
