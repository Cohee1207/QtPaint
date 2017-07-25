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

#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "linetool.h"

class EllipseTool : public LineTool {
public:
    EllipseTool(PaintArea*);

    // PaintTool interface
public:
    virtual const QString toolName() override;
    virtual const QString iconName() override;
    virtual void onMouseMove(const QPoint&) override;
    virtual void onMouseRelease(const QPoint&) override;

protected:
    virtual void paint(const QPoint&, bool temporary) override;
};

#endif // ELLIPSETOOL_H
