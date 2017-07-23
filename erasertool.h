#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include <QPoint>
#include <QPen>
#include "painttool.h"

class EraserTool : public PaintTool {
public:
    EraserTool(PaintArea*);

    // PaintTool interface
public:
    const QString toolName() override;
    const QString iconName() override;
    virtual void onMousePress(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;
    virtual void onMouseMove(const QPoint&) override;
private:
    QPen m_eraser;

    void eraseLine(const QPoint& p1, const QPoint& p2);
    void erasePoint(const QPoint& c);
};

#endif // ERASERTOOL_H
