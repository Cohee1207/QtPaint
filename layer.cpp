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
