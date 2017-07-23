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
    clearBlankPixmap();
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
    clearBlankPixmap();
}
