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

#include "paintevent.h"

class PaintArea;

class PaintTool {
public:
    virtual const QString toolName() = 0;
    virtual const QString iconName() = 0;
    virtual void onMousePress(PaintEvent*) = 0;
    virtual void onMouseRelease(PaintEvent*) = 0;
    virtual void onMouseMove(PaintEvent*) = 0;
};

#endif // PAINTTOOL_H
