#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "linetool.h"

class RectangleTool : public LineTool {
public:
    RectangleTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMouseMove(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;

    // LineTool interface
protected:

    virtual void paint(const QPoint&, bool temporary) override;
};

#endif // RECTANGLETOOL_H
