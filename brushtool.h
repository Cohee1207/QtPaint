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

#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include <QPoint>
#include "painttool.h"


class BrushTool : public PaintTool {
public:
    BrushTool(PaintArea*);

    // PaintTool interface
public:
    const QString toolName() override;
    const QString iconName() override;
    virtual void onMousePress(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;
    virtual void onMouseMove(const QPoint&) override;
private:
    void paintLine(const QPoint& p1, const QPoint& p2);
    void paintPoint(const QPoint& c);
};

#endif // BRUSHTOOL_H
