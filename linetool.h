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

#ifndef LINETOOL_H
#define LINETOOL_H

#include "painttool.h"

class LineTool : public PaintTool {
public:
    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMousePress(PaintEvent*) override;
    virtual void onMouseRelease(PaintEvent*) override;
    virtual void onMouseMove(PaintEvent*) override;
protected:
    QPoint m_originPoint;
    virtual void paint(PaintEvent* event, bool temporary);
    void clearToolLayer(QPixmap*);
};

#endif // LINETOOL_H
