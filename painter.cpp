#include "painter.h"

Painter::Painter(PaintArea* parent) : m_parent(parent), m_points(parent->points()), m_mutex(parent->vectorMutex())
{

}

void Painter::run()
{
    while (true) {
        //if (m_mutex->tryLock()) {
        if (m_points->empty()) {
            continue;
        }
        auto image = m_parent->overlayImage();
        auto color = m_parent->brushColor();
        auto point = m_points->front();
        auto radius = m_parent->brushRadius();
        for (int y = -radius; y <= radius; y++) {
            for (int x = -radius; x <= radius; x++) {
                if (x * x + y * y <= radius * radius) {
                    image.setPixel(point.x() + x, point.y() + y, color.rgb());
                }
            }
        }
        m_points->pop_front();
//            m_mutex->unlock();
        //}
    }
}
