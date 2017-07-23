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
        QColor blendColor;

        for (int i = 0; i < 4; i++) {

            next = pt;
            next.rx() += rx[(i + j) % 4];
            next.ry() += ry[(i + j) % 4];

            if (valid(next) && canFill(image, next, oldColor, blendColor)) {
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
bool FloodFillTool::canFill(const QImage* image, const QPoint& pt, const QColor& oldColor, QColor& blendColor)
{
    QColor pixelColor = image->pixelColor(pt);
    if (pixelColor == oldColor && pixelColor.alpha() <= m_fillColor.alpha()) {
        return true;
    }
    return false;
    if (pixelColor == QColor(Qt::black)) {
        qDebug() << "In black";
    }
    if (pixelColor == m_fillColor && pixelColor.alpha() == m_fillColor.alpha())
        return false;
    qreal r = oldColor.redF() - pixelColor.redF();
    qreal g = oldColor.greenF() - pixelColor.greenF();
    qreal b = oldColor.blueF() - pixelColor.blueF();

    qreal diff = sqrt(r * r + g * g + b * b);

    // If difference above this threshold, filling stops.
    const qreal threshold1 = 0.4;
    // If difference above this threshold, blending occurs.
    const qreal threshold2 = 0.3;

    if (diff > threshold1) {
        return false;
    }
    else if (diff > threshold2) {
        blendColor.setRedF(m_fillColor.redF() * (1 - diff) + pixelColor.redF() * (diff));
        blendColor.setGreenF(m_fillColor.greenF() * (1 -  diff) + pixelColor.greenF() * (diff));
        blendColor.setBlueF(m_fillColor.blueF() * (1 - diff) + pixelColor.blueF() * (diff));
        return true;
    }
    else if (diff <= 0.05) {
        blendColor = m_fillColor;
        return false;
    }
    return true;
}

// Only draw valid points as image may be larger than visible area
bool FloodFillTool::valid(const QPoint& pt)
{
    return (pt.x() >= 0 && pt.x() < imageWidth && pt.y() >= 0 && pt.y() < imageHeight);
}

