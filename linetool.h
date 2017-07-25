#ifndef LINETOOL_H
#define LINETOOL_H

#include "painttool.h"

class LineTool : public PaintTool {
public:
    LineTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMousePress(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;
    virtual void onMouseMove(const QPoint&) override;
protected:
    QPoint m_originPoint;
    virtual void paint(const QPoint&, bool temporary);
    void clearToolLayer();
};

#endif // LINETOOL_H
