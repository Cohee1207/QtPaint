#include "painttool.h"
#include "paintarea.h"
#include <QPainter>

void PaintTool::clearBlankPixmap()
{
    auto pixmap = m_area->toolLayer();
    QPainter painter(pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painter.fillRect(pixmap->rect(), Qt::black);
}
