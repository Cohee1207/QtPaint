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

#include "floodfilltool.h"
#include <QStack>
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <vector>
#include "paintarea.h"

FloodFillTool::FloodFillTool(PaintArea* area) : PaintTool(area)
{

}

const QString FloodFillTool::toolName()
{
    static const QString floodFillName = "Flood fill";
    return floodFillName;
}

const QString FloodFillTool::iconName()
{
    static const QString floodFillIcon = "color";
    return floodFillIcon;
}

void FloodFillTool::onMousePress(const QPoint& p)
{
    m_fillColor = m_area->pen().color();
    imageHeight = m_area->selectedLayer()->height();
    imageWidth = m_area->selectedLayer()->width();
    floodFill(p);
}

void FloodFillTool::onMouseRelease(const QPoint&)
{

}

void FloodFillTool::onMouseMove(const QPoint&)
{

}

void FloodFillTool::floodFill(const QPoint& point)
{
    QImage* image = m_area->selectedLayer();
    QPainter painter(image);
    painter.setPen(m_fillColor);
    QColor oldColor = image->pixelColor(point);

    // The stack of pixels to fill
    QStack<QPoint> pixels;

    // Add the initial point
    pixels.append(point);

    const int rx[] = { -1,  0, +1, 0 };
    const int ry[] = {  0, +1, 0, -1 };

    int j = 0;
    while (!pixels.empty()) {
        QPoint pt = pixels.takeLast();

        QPoint next;

        for (int i = 0; i < 4; i++) {

            next = pt;
            next.rx() += rx[(i + j) % 4];
            next.ry() += ry[(i + j) % 4];

            if (valid(next) && canFill(image, next, oldColor)) {
                painter.drawPoint(next);
                pixels.append(next);
            }
        }
        j++;
        // no infinite loops
        if (pixels.size() > imageWidth * imageHeight) {
            break;
        }
    }
}


// Determine if the pixel should be filled
bool FloodFillTool::canFill(const QImage* image, const QPoint& pt, const QColor& oldColor)
{
    QColor pixelColor = image->pixelColor(pt);
    if (pixelColor == oldColor && pixelColor.alpha() <= m_fillColor.alpha()) {
        return true;
    }
    return false;
}

// Only draw valid points as image may be larger than visible area
bool FloodFillTool::valid(const QPoint& pt)
{
    return (pt.x() >= 0 && pt.x() < imageWidth && pt.y() >= 0 && pt.y() < imageHeight);
}

