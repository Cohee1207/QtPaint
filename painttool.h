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

#ifndef PAINTTOOL_H
#define PAINTTOOL_H

#include <QString>
#include <QMouseEvent>

class PaintArea;

class PaintTool {
public:
    virtual const QString toolName() = 0;
    virtual const QString iconName() = 0;
    virtual void onMousePress(const QPoint&) = 0;
    virtual void onMouseRelease(const QPoint&) = 0;
    virtual void onMouseMove(const QPoint&) = 0;
    virtual ~PaintTool() {}
    PaintTool(PaintArea* area) : m_area(area) {}
protected:
    PaintArea* m_area;
};

#endif // PAINTTOOL_H
