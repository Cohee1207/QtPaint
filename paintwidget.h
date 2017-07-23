#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

class PaintArea;

class PaintWidget : public QWidget {
    Q_OBJECT
public:
    explicit PaintWidget(PaintArea* parent = nullptr);
    // qwidget overrides
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
signals:
    void mousePress(const QPoint&, int button);
    void mouseMove(const QPoint&);
    void mouseRelease(const QPoint&, int button);
private:
    QBrush brush;
    PaintArea* m_area;
};

#endif // PAINTWIDGET_H
