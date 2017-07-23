#ifndef FLOODFILLTOOL_H
#define FLOODFILLTOOL_H

#include "painttool.h"
#include <QColor>

class FloodFillTool : public PaintTool {
public:
    FloodFillTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMousePress(const QPoint& p) override;
    virtual void onMouseRelease(const QPoint& p) override;
    virtual void onMouseMove(const QPoint& p) override;
private:
    QColor m_fillColor;
    int imageWidth;
    int imageHeight;
    void floodFill(const QPoint&);
    bool valid(const QPoint&);
    bool canFill(const QImage*, const QPoint&, const QColor&, QColor&);
};

#endif // FLOODFILLTOOL_H
