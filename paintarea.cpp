#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QDebug>
#include <QBitmap>
#include <QClipboard>
#include <QTransform>

#include "paintarea.h"

static const QString LAYER_NAME = QStringLiteral("Layer");
static const int DEFAULT_ZOOM = 100;

PaintArea::PaintArea(QWidget* parent) : QScrollArea(parent), m_paintWidget(new PaintWidget(this))
{
    m_antialiasingEnabled = false;
    m_selectedTool = 0;
    m_selectedLayer = 0;
    m_brush = QColor(0xFF, 0xFF, 0xFF, 0x00);
    m_zoom = DEFAULT_ZOOM;
    setAlignment(Qt::AlignCenter);
    setBackgroundRole(QPalette::Midlight);
    setRepaintTimer();
    setDefaultLayer();
    setDefaultPen();
    setPaintTools();
    setWidget(m_paintWidget);
    connect(m_paintWidget, &PaintWidget::mouseMove, this, &PaintArea::mouseMove);
    connect(m_paintWidget, &PaintWidget::mouseRelease, this, &PaintArea::mouseRelease);
    connect(m_paintWidget, &PaintWidget::mousePress, this, &PaintArea::mousePress);
}

int PaintArea::increasePenWidth()
{
    auto width = m_pen.width();
    if (width < MAX_PEN_WIDTH) {
        m_pen.setWidth(++width);
        return width;
    }
    return width;
}

int PaintArea::decreasePenWidth()
{
    auto width = m_pen.width();
    if (width > MIN_PEN_WIDTH) {
        m_pen.setWidth(--width);
        return width;
    }
    return width;
}

void PaintArea::setPenColor(const QColor& color)
{
    m_pen.setColor(color);
}

void PaintArea::setPenWidth(int value)
{
    m_pen.setWidth(value);
}

PaintArea::~PaintArea()
{

}

bool PaintArea::loadImage(const QString& path)
{
    auto image = QImage();
    bool success = image.load(path);
    if (!success) {
        return false;
    }
    image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    m_layers.clear();
    m_layers.append(Layer(image, LAYER_NAME));
    m_selectedLayer = 0;
    m_paintWidget->resize(image.size());
    setToolLayer(image.size());
    return true;
}

QSize PaintArea::imageSize() const
{
    return m_paintWidget->size();
}

void PaintArea::setLayerVisible(int index, bool visible)
{
    if (index < 0 || index > m_layers.size()) {
        qDebug() << "Invalid index in PaintArea::setLayerVisible: " << index;
        return;
    }
    m_layers[index].setVisible(visible);
}

QImage* PaintArea::selectedLayer()
{
    return m_layers[m_selectedLayer].image();
}

QImage* PaintArea::layerImageAt(int i)
{
    return m_layers[i].image();
}

bool PaintArea::layerVisibleAt(int i)
{
    return m_layers[i].visible();
}

int PaintArea::layersCount() const
{
    return m_layers.size();
}

void PaintArea::setDefaultLayer(int width, int height, QColor fill)
{
    auto pixmap = QPixmap(width, height);
    pixmap.fill(fill);
    QImage image = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
    m_layers.clear();
    m_layers.append(Layer(image, LAYER_NAME));
    m_selectedLayer = 0;
    m_paintWidget->resize(width, height);
    setToolLayer(QSize(width,height));
}

void PaintArea::mouseMove(const QPoint& pos)
{
    if (m_collectMouseMove) {
        auto adjusted = adjustedPos(pos);
        m_tools[m_selectedTool]->onMouseMove(adjusted);
        m_prevPoint = adjusted;
        _update_proxy();
    }
}

void PaintArea::mousePress(const QPoint& pos, int button)
{
    if (button == Qt::LeftButton && m_layers[m_selectedLayer].visible()) {
        m_collectMouseMove = true;
        auto adjusted = adjustedPos(pos);
        m_prevPoint = adjusted;
        m_tools[m_selectedTool]->onMousePress(adjusted);
        _update_proxy();
    }
}

void PaintArea::mouseRelease(const QPoint& pos, int button)
{
    if (button == Qt::LeftButton) {
        m_collectMouseMove = false;
        m_tools[m_selectedTool]->onMouseRelease(adjustedPos(pos));
        _update_proxy();
    }
}

void PaintArea::_update_proxy()
{
    m_paintWidget->repaint();
}

QImage PaintArea::saveImage()
{
    if (m_layers.size() == 0) {
        return QImage();
    }
    auto pixmap = QPixmap(m_paintWidget->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    for (int i = 0; i < m_layers.size(); i++) {
        if (m_layers[i].visible()) {
            auto image = m_layers[i].image();
            painter.drawImage(QPoint(0, 0), *image);
        }
    }
    return pixmap.toImage();
}

void PaintArea::setRepaintTimer()
{
    static const int REPAINT_RATE = 500; // 2 fps
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PaintArea::_update_proxy);
    timer->start(REPAINT_RATE);
}

void PaintArea::setDefaultPen()
{
    static const int DEFAULT_PEN_WIDTH = 5;
    static const QColor DEFAULT_PEN_COLOR = QColor(Qt::black);
    m_pen.setCapStyle(Qt::RoundCap);
    m_pen.setJoinStyle(Qt::MiterJoin);
    m_pen.setColor(DEFAULT_PEN_COLOR);
    m_pen.setWidth(DEFAULT_PEN_WIDTH);
}

void PaintArea::setPaintTools()
{
}

void PaintArea::setToolLayer(const QSize & size)
{
    m_toolLayer = QPixmap(size);
    m_toolLayer.fill(Qt::transparent);
}


void PaintArea::rotate(int degree)
{
    if (m_layers.size() == 0) {
        return;
    }
    auto transform = new QTransform();
    transform->rotate(qreal(degree));
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->transformed(*transform));
    }
    delete transform;
    auto size = m_layers[0].image()->size();
    m_paintWidget->resize(size);
    setToolLayer(size);
}

void PaintArea::flipHorizontal()
{
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->mirrored(true,false));
    }
}

void PaintArea::flipVertical()
{
    for(int i = 0; i < m_layers.size(); i++) {
        m_layers[i].setImage(m_layers[i].image()->mirrored(false,true));
    }
}

int PaintArea::zoom() const
{
    return m_zoom;
}

void PaintArea::setZoom(int zoom)
{
    m_zoom = zoom;
    rezoom();
}

void PaintArea::rezoom()
{
    if (m_layers.size() == 0) {
        return;
    }
    auto layerSize = m_layers[0].image()->size();
    auto newSize = layerSize * (m_zoom / 100.0);
    m_paintWidget->resize(newSize);
}

QPoint PaintArea::adjustedPos(const QPoint & pos)
{
    if (m_layers.size() == 0) {
        return pos;
    }
    auto factor = 100.0 / m_zoom;
    return pos * factor;
}


QBrush PaintArea::brush() const
{
    return m_brush;
}

void PaintArea::setBrushColor(const QColor& color)
{
    m_brush.setColor(color);
}

bool PaintArea::antialiasingEnabled() const
{
    return m_antialiasingEnabled;
}

void PaintArea::setAntialiasingEnabled(bool antialiasingEnabled)
{
    m_antialiasingEnabled = antialiasingEnabled;
}

const QVector<PaintTool*>* PaintArea::tools() const
{
    return &m_tools;
}

QPoint PaintArea::prevPoint() const
{
    return m_prevPoint;
}

int PaintArea::selectedTool() const
{
    return m_selectedTool;
}

void PaintArea::setSelectedTool(int i)
{
    m_selectedTool = i;
}

QPixmap* PaintArea::toolLayer()
{
    return &m_toolLayer;
}

bool PaintArea::pasteImage()
{
    auto clipboard = QApplication::clipboard();
    QImage image = clipboard->image();
    if (image.isNull()) {
        return false;
    }
    m_layers.append(Layer(image, QStringLiteral("Pasted")));
    return true;
}

void PaintArea::copyImage()
{
    auto clipboard = QApplication::clipboard();
    clipboard->setImage(saveImage());
}

QPen PaintArea::pen() const
{
    return m_pen;
}

void PaintArea::transform(int type)
{
    switch(type) {
    case FLIP_HORIZONTAL:
        flipHorizontal();
        break;
    case FLIP_VERTICAL:
        flipVertical();
        break;
    case ROTATE_LEFT:
    case ROTATE_RIGHT:
        rotate(type);
        break;
    }
}
