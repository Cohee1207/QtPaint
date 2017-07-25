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

#include "paintwidget.h"
#include "paintarea.h"
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <QMouseEvent>
#include <memory>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), m_selectedLayer(0)
{
    QCursor cursor;
    cursor.setShape(Qt::CrossCursor);
    setCursor(cursor);
    QBitmap bitmap;
    if (!bitmap.load(QStringLiteral(":/background.bmp"))){
        qDebug() << "Can't load bitmap";
    }
    m_checkeredBackground.setTexture(bitmap);
    m_checkeredBackground.setColor(Qt::gray);
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMove(event->pos(), m_layers[m_selectedLayer].image());
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_layers[m_selectedLayer].visible()) {
        emit mousePress(event->pos(), m_layers[m_selectedLayer].image());
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit mouseRelease(event->pos(), m_layers[m_selectedLayer].image());
    }
}

void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), m_checkeredBackground);
    for (int i = 0; i < m_layers.size(); i++) {
        if (m_layers[i].visible()) {
            painter.drawImage(QPoint(0, 0), *m_layers[i].image());
        }
    }
    painter.drawPixmap(QPoint(0, 0), m_toolLayer);
}

QPixmap *PaintWidget::toolLayer()
{
    return &m_toolLayer;
}

void PaintWidget::rezoom(int zoom)
{
    if (m_layers.size() == 0) {
        return;
    }
    auto layerSize = m_layers[0].image()->size();
    auto newSize = layerSize * (zoom / 100.0);
    resize(newSize);
}

void PaintWidget::setLayerVisible(int index, bool visible)
{
    if (index < 0 || index > m_layers.size()) {
        return;
    }
    m_layers[index].setVisible(visible);
}

void PaintWidget::rotate(int degree)
{
    if (m_layers.size() == 0) {
        return;
    }
    std::unique_ptr<QTransform> transform(new QTransform);
    transform->rotate(qreal(degree));
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->transformed(*transform));
    }
    auto size = m_layers[0].image()->size();
    resize(size);
    setToolLayer(size);
}

void PaintWidget::flipHorizontal()
{
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->mirrored(true,false));
    }
}

void PaintWidget::flipVertical()
{
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->mirrored(false,true));
    }
}

void PaintWidget::setToolLayer(const QSize & size)
{
    m_toolLayer = QPixmap(size);
    m_toolLayer.fill(Qt::transparent);
}

QImage PaintWidget::renderImage()
{
    if (m_layers.size() == 0) {
        return QImage();
    }
    auto pixmap = QPixmap(size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    for (int i = 0; i < m_layers.size(); i++) {
        if (m_layers[i].visible()) {
            auto image = m_layers[i].image();
            painter.drawImage(QPoint(0, 0), *image);
        }
    }
    return pixmap.toImage();
}

void PaintWidget::setSingleLayer(const QImage& image)
{
    m_layers.clear();
    m_layers.append(Layer(image));
    m_selectedLayer = 0;
    resize(image.size());
    setToolLayer(image.size());
    repaint();
}

void PaintWidget::addLayer(const QImage & image, const QString & name)
{
    if (m_layers.size() != 0) {
        auto currentSize = m_layers[0].image()->size();
        if(image.size() != currentSize) {
            /// TODO: Add pasted layer to selection when selection is implemented
            QPixmap pixmap(currentSize);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.drawImage(QPoint(0,0), image);
            m_layers.append(Layer(pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied), name));
        } else {
            m_layers.append(Layer(image,name));
        }
    }
    m_selectedLayer = m_layers.size() - 1;
}
