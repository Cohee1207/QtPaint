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

PaintWidget::PaintWidget(PaintArea* parent) : QWidget(parent), m_area(parent)
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
    emit mouseMove(event->pos());
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    emit mousePress(event->pos(), event->button());
}

void PaintWidget::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseRelease(event->pos(), event->button());
}

void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), m_checkeredBackground);
    for (int i = 0; i < m_area->layersCount(); i++) {
        if (m_area->layerVisibleAt(i)) {
            auto image = m_area->layerImageAt(i);
            painter.drawImage(rect(), *image);
        }
    }
    painter.drawPixmap(rect(), *m_area->toolLayer());
}
