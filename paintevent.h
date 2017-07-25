#ifndef PAINTEVENT_H
#define PAINTEVENT_H

#include <QPixmap>
#include <QBrush>
#include <QPen>

struct PaintEvent {
    QPen pen;
    QBrush brush;
    QImage* selectedLayer;
    QPixmap* toolLayer;
    QPoint currentPoint;
    QPoint previousPoint;
    bool antialiasingEnabled;
};

#endif // PAINTEVENT_H
