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

#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QBitmap>
#include <QClipboard>
#include <QTransform>
#include <memory>

#include "paintarea.h"
#include "paintevent.h"

static const int DEFAULT_ZOOM = 100;

PaintArea::PaintArea(QWidget* parent) : QScrollArea(parent), m_paintWidget(new PaintWidget())
{
    m_antialiasingEnabled = false;
    m_selectedTool = 0;
    m_brush = QColor(0xFF, 0xFF, 0xFF, 0x00);
    m_zoom = DEFAULT_ZOOM;
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Midlight);
    setBlankLayer();
    setDefaultPen();
    setWidget(m_paintWidget);
    connect(m_paintWidget, &PaintWidget::mouseMove, this, &PaintArea::mouseMove);
    connect(m_paintWidget, &PaintWidget::mouseRelease, this, &PaintArea::mouseRelease);
    connect(m_paintWidget, &PaintWidget::mousePress, this, &PaintArea::mousePress);
}

void PaintArea::setPenColor(const QColor& color)
{
    m_pen.setColor(color);
}

void PaintArea::setPenWidth(int value)
{
    m_pen.setWidth(value);
}

PaintArea::~PaintArea()
{
    delete m_paintWidget;
}

bool PaintArea::loadImage(const QString& path)
{
    auto image = QImage();
    bool success = image.load(path);
    if (!success) {
        return false;
    }
    image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    m_paintWidget->setSingleLayer(image);
    return true;
}

QSize PaintArea::imageSize() const
{
    return m_paintWidget->size();
}

void PaintArea::setBlankLayer(int width, int height, QColor fill)
{
    auto pixmap = QPixmap(width, height);
    pixmap.fill(fill);
    QImage image = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
    m_paintWidget->setSingleLayer(image);
}

void PaintArea::mouseMove(const QPoint& pos, QImage* layer)
{
    if (m_collectMouseMove) {
        auto adjusted = adjustedPos(pos);
        std::shared_ptr<PaintEvent> event (fillPaintEvent(adjusted,layer));
        m_tools[m_selectedTool]->onMouseMove(event.get());
        m_prevPoint = adjusted;
        m_paintWidget->repaint();
    }
}

void PaintArea::mousePress(const QPoint& pos, QImage* layer)
{
    m_collectMouseMove = true;
    auto adjusted = adjustedPos(pos);
    m_prevPoint = adjusted;
    std::shared_ptr<PaintEvent> event (fillPaintEvent(adjusted,layer));
    m_tools[m_selectedTool]->onMousePress(event.get());
    m_paintWidget->repaint();
}

void PaintArea::mouseRelease(const QPoint& pos, QImage* layer)
{
    m_collectMouseMove = false;
    std::shared_ptr<PaintEvent> event (fillPaintEvent(adjustedPos(pos),layer));
    m_tools[m_selectedTool]->onMouseRelease(event.get());
    m_paintWidget->repaint();
}

QImage PaintArea::saveImage()
{
    return m_paintWidget->renderImage();
}

void PaintArea::setDefaultPen()
{
    static const int DEFAULT_PEN_WIDTH = 5;
    static const QColor DEFAULT_PEN_COLOR = QColor(Qt::black);
    m_pen.setCapStyle(Qt::RoundCap);
    m_pen.setJoinStyle(Qt::MiterJoin);
    m_pen.setColor(DEFAULT_PEN_COLOR);
    m_pen.setWidth(DEFAULT_PEN_WIDTH);
}


PaintEvent *PaintArea::fillPaintEvent(const QPoint& point, QImage * layer)
{
    auto event = new PaintEvent;
    event->antialiasingEnabled = m_antialiasingEnabled;
    event->brush = m_brush;
    event->currentPoint = point;
    event->pen = m_pen;
    event->previousPoint = m_prevPoint;
    event->selectedLayer = layer;
    event->toolLayer = m_paintWidget->toolLayer();
    return event;
}

int PaintArea::zoom() const
{
    return m_zoom;
}

void PaintArea::setZoom(int zoom)
{
    m_zoom = zoom;
    m_paintWidget->rezoom(zoom);
}


QPoint PaintArea::adjustedPos(const QPoint & pos)
{
    auto factor = 100.0 / m_zoom;
    return pos * factor;
}


QBrush PaintArea::brush() const
{
    return m_brush;
}

void PaintArea::setBrushColor(const QColor& color)
{
    m_brush.setColor(color);
}

bool PaintArea::antialiasingEnabled() const
{
    return m_antialiasingEnabled;
}

void PaintArea::setAntialiasingEnabled(bool antialiasingEnabled)
{
    m_antialiasingEnabled = antialiasingEnabled;
}

const QVector<PaintTool*>* PaintArea::tools() const
{
    return &m_tools;
}

int PaintArea::selectedTool() const
{
    return m_selectedTool;
}

void PaintArea::setSelectedTool(int i)
{
    m_selectedTool = i;
}

bool PaintArea::pasteImage()
{
    auto clipboard = QApplication::clipboard();
    QImage image = clipboard->image();
    if (image.isNull()) {
        return false;
    }
    m_paintWidget->addLayer(image, QStringLiteral("Pasted"));
    return true;
}

void PaintArea::copyImage()
{
    auto clipboard = QApplication::clipboard();
    clipboard->setImage(saveImage());
}

QPen PaintArea::pen() const
{
    return m_pen;
}

void PaintArea::transform(int type)
{
    switch(type) {
    case FLIP_HORIZONTAL:
        m_paintWidget->flipHorizontal();
        break;
    case FLIP_VERTICAL:
        m_paintWidget->flipVertical();
        break;
    case ROTATE_LEFT:
    case ROTATE_RIGHT:
        m_paintWidget->rotate(type);
        break;
    }
    m_paintWidget->repaint();
}
