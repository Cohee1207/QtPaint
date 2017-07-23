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
    brush.setTexture(bitmap);
    brush.setColor(Qt::gray);
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
    painter.fillRect(rect(), brush);
    for (int i = 0; i < m_area->layersCount(); i++) {
        if (m_area->layerVisibleAt(i)) {
            auto image = m_area->layerImageAt(i);
            painter.drawImage(rect(), *image);
        }
    }
    painter.drawPixmap(rect(), *m_area->toolLayer());
}
