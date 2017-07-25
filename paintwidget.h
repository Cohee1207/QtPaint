/*
Copyright 2017 SillyLossy.
This program is free software; you can redistribute it and/or
modify it under the terms of the Lesser GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the Lesser GNU General Public License for more details.
You should have received a copy of the Lesser GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include "layer.h"

class PaintWidget : public QWidget {
    Q_OBJECT
public:
    explicit PaintWidget(QWidget* parent = nullptr);
    // qwidget overrides
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    QPixmap* toolLayer();
    void setSingleLayer(const QImage&);
    void addLayer(const QImage&, const QString&);
    void setToolLayer(const QSize&);
    QImage renderImage();
    void rotate(int degree);
    void flipHorizontal();
    void flipVertical();
    void rezoom(int zoom);

    void setLayerVisible(int index, bool visible);

signals:
    void mousePress(const QPoint&, QImage*);
    void mouseMove(const QPoint&, QImage*);
    void mouseRelease(const QPoint&, QImage*);
private:
    QBrush m_checkeredBackground;

    int m_selectedLayer;

    QVector<Layer> m_layers;

    QPixmap m_toolLayer;
};

#endif // PAINTWIDGET_H
