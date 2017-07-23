#include "brushtool.h"
#include "paintarea.h"

#include <QPainter>


BrushTool::BrushTool(PaintArea* area) : PaintTool(area)
{

}

const QString BrushTool::toolName()
{
    static const QString brushName = QStringLiteral("Brush");
    return brushName;
}

const QString BrushTool::iconName()
{
    static const QString brushIcon = QStringLiteral("brush");
    return brushIcon;
}

void BrushTool::onMousePress(const QPoint& p)
{
    paintPoint(p);
}

void BrushTool::onMouseRelease(const QPoint&)
{

}

void BrushTool::onMouseMove(const QPoint& p)
{
    paintLine(m_area->prevPoint(), p);
}

void BrushTool::paintLine(const QPoint& p1, const QPoint& p2)
{
    QPainter painter(m_area->selectedLayer());
    if (m_area->antialiasingEnabled())
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(m_area->pen());
    painter.drawLine(p1, p2);
}

void BrushTool::paintPoint(const QPoint& c)
{
    QPainter painter(m_area->selectedLayer());
    if (m_area->antialiasingEnabled())
        painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(m_area->pen());
    painter.drawPoint(c);
}
