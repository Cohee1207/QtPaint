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

#include "layer.h"

Layer::Layer() : m_image(QImage()), m_name("Null layer"), m_visible(false)
{

}

Layer::Layer(const QImage& image, const QString& name, bool visible) : m_image(image), m_name(name), m_visible(visible)
{

}

QString Layer::name() const
{
    return m_name;
}

void Layer::setName(const QString& name)
{
    m_name = name;
}

bool Layer::visible() const
{
    return m_visible;
}

void Layer::setVisible(bool value)
{
    m_visible = value;
}

QImage* Layer::image()
{
    return &m_image;
}

void Layer::setImage(const QImage &image)
{
    m_image = image;
}
