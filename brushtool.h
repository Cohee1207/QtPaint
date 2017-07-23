#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QPoint>
#include "painttool.h"


class BrushTool : public PaintTool {
public:
    BrushTool(PaintArea*);

    // PaintTool interface
public:
    const QString toolName() override;
    const QString iconName() override;
    virtual void onMousePress(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;
    virtual void onMouseMove(const QPoint&) override;
private:
    void paintLine(const QPoint& p1, const QPoint& p2);
    void paintPoint(const QPoint& c);
};

#endif // BRUSHTOOL_H
