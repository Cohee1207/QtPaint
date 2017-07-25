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

#include "erasertool.h"
#include "paintarea.h"
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QBitmap>

EraserTool::EraserTool()
{
    m_eraser.setCapStyle(Qt::RoundCap);
    m_eraser.setColor(QColor(Qt::black));
}

const QString EraserTool::toolName()
{
    static const QString eraserName = QStringLiteral("Eraser");
    return eraserName;
}

const QString EraserTool::iconName()
{
    static const QString eraserIcon = QStringLiteral("eraser");
    return eraserIcon;
}

void EraserTool::onMousePress(PaintEvent * event)
{
    erasePoint(event);
}

void EraserTool::onMouseRelease(PaintEvent*)
{

}

void EraserTool::onMouseMove(PaintEvent* event)
{
    eraseLine(event);
}

void EraserTool::eraseLine(PaintEvent* event)
{
    QPainter painter(event->selectedLayer);
    if (event->antialiasingEnabled)
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    m_eraser.setWidth(event->pen.width());
    painter.setPen(m_eraser);
    painter.drawLine(event->previousPoint, event->currentPoint);
}

void EraserTool::erasePoint(PaintEvent * event)
{
    QPainter painter(event->selectedLayer);
    if (event->antialiasingEnabled)
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    m_eraser.setWidth(event->pen.width());
    painter.setPen(m_eraser);
    painter.drawPoint(event->currentPoint);
}
