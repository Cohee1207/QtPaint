#ifndef LAYER_H
#define LAYER_H

#include <QImage>
#include <QString>

class Layer {
private:
    QImage m_image;
    QString m_name;
    bool m_visible;
public:
    Layer();
    Layer(const QImage& image, const QString& name, bool m_visible = true);
    QString name() const;
    void setName(const QString& name);
    bool visible() const;
    void setVisible(bool value);
    QImage* image();
    void setImage(const QImage& image);
};

#endif // LAYER_H
