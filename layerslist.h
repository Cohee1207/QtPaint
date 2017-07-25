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

#ifndef LAYERSLIST_H
#define LAYERSLIST_H

#include <QWidget>

namespace Ui {
class LayersList;
}

class LayersList : public QWidget
{
    Q_OBJECT

public:
    explicit LayersList(QWidget *parent = 0);
    ~LayersList();

private:
    Ui::LayersList *ui;
};

#endif // LAYERSLIST_H
