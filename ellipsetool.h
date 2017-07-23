#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "linetool.h"

class EllipseTool : public LineTool {
public:
    EllipseTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMouseMove(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;

protected:
    virtual void paint(const QPoint&, bool temporary) override;
};

#endif // ELLIPSETOOL_H
