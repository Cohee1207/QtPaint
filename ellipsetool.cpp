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
    clearBlankPixmap();
}
