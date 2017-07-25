#include "linetool.h"
#include "paintarea.h"
#include "QPainter"
#include <QDebug>

LineTool::LineTool(PaintArea* area) : PaintTool(area)
{

}

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

void LineTool::onMousePress(const QPoint& p)
{
    m_originPoint = p;
}

void LineTool::onMouseRelease(const QPoint& p)
{
    paint(p, false);
    clearToolLayer();
}

void LineTool::onMouseMove(const QPoint& p)
{
    paint(p, true);
}

void LineTool::paint(const QPoint& p, bool temporary)
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
    painter.drawLine(m_originPoint, p);
}

void LineTool::clearToolLayer()
{
    m_area->toolLayer()->fill(Qt::transparent);
}

