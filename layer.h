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

#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QString>

static const QString LAYER_NAME = QStringLiteral("Layer");

class Layer {
private:
    QImage m_image;
    QString m_name;
    bool m_visible;
public:
    Layer();
    Layer(const QImage& image, const QString& name = LAYER_NAME, bool m_visible = true);
    QString name() const;
    void setName(const QString& name);
    bool visible() const;
    void setVisible(bool value);
    QImage* image();
    void setImage(const QImage& image);
};

#endif // LAYER_H
