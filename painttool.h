#ifndef PAINTTOOL_H
#define PAINTTOOL_H

#include <QString>
#include <QMouseEvent>

class PaintArea;

class PaintTool {
public:
    virtual const QString toolName() = 0;
    virtual const QString iconName() = 0;
    virtual void onMousePress(const QPoint&) = 0;
    virtual void onMouseRelease(const QPoint&) = 0;
    virtual void onMouseMove(const QPoint&) = 0;
    virtual ~PaintTool() {}
    PaintTool(PaintArea* area) : m_area(area) {}
protected:
    PaintArea* m_area;
    void clearBlankPixmap();
};

#endif // PAINTTOOL_H
