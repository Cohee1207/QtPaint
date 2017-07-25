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

#ifndef FLOODFILLTOOL_H
#define FLOODFILLTOOL_H

#include "painttool.h"
#include <QColor>

class FloodFillTool : public PaintTool {
public:
    FloodFillTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMousePress(const QPoint& p) override;
    virtual void onMouseRelease(const QPoint& p) override;
    virtual void onMouseMove(const QPoint& p) override;
private:
    QColor m_fillColor;
    int imageWidth;
    int imageHeight;
    void floodFill(const QPoint&);
    bool valid(const QPoint&);
    bool canFill(const QImage*, const QPoint&, const QColor&);
};

#endif // FLOODFILLTOOL_H
