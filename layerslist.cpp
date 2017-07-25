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

#include "layerslist.h"
#include "ui_layerslist.h"

LayersList::LayersList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayersList)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Tool);
}

LayersList::~LayersList()
{
    delete ui;
}
