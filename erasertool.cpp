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

EraserTool::EraserTool(PaintArea* area) : PaintTool(area)
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

void EraserTool::onMousePress(const QPoint& p)
{
    erasePoint(p);
}

void EraserTool::onMouseRelease(const QPoint&)
{

}

void EraserTool::onMouseMove(const QPoint& p)
{
    eraseLine(m_area->prevPoint(), p);
}

void EraserTool::eraseLine(const QPoint& p1, const QPoint& p2)
{
    QPainter painter(m_area->selectedLayer());
    if (m_area->antialiasingEnabled())
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    m_eraser.setWidth(m_area->pen().width());
    painter.setPen(m_eraser);
    painter.drawLine(p1, p2);
}

void EraserTool::erasePoint(const QPoint& c)
{
    QPainter painter(m_area->selectedLayer());
    if (m_area->antialiasingEnabled())
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    m_eraser.setWidth(m_area->pen().width());
    painter.setPen(m_eraser);
    painter.drawPoint(c);
}
