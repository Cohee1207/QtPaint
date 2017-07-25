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

#include "linetool.h"
#include "paintarea.h"
#include "QPainter"
#include <QDebug>

const QString LineTool::toolName()
{
    static const QString lineName = QStringLiteral("Line");
    return lineName;
}

const QString LineTool::iconName()
{
    static const QString lineIcon = QStringLiteral("line");
    return lineIcon;
}

void LineTool::onMousePress(PaintEvent* event)
{
    m_originPoint = event->currentPoint;
}

void LineTool::onMouseRelease(PaintEvent* event)
{
    paint(event, false);
    clearToolLayer(event->toolLayer);
}

void LineTool::onMouseMove(PaintEvent* event)
{
    paint(event, true);
}

void LineTool::paint(PaintEvent* event, bool temporary)
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
    painter.drawLine(m_originPoint, event->currentPoint);
}

void LineTool::clearToolLayer(QPixmap* layer)
{
    layer->fill(Qt::transparent);
}

