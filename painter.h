#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QThread>
#include "paintarea.h"

class Painter : public QThread {
    Q_OBJECT
public:
    Painter(PaintArea* parent);
private:
    PaintArea* m_parent;
    QVector<QPoint>* m_points;
    QMutex* m_mutex;
    void run() override;
};

#endif // PAINTER_H
