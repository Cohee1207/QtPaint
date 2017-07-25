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

#ifndef ZOOMSLIDER_H
#define ZOOMSLIDER_H

#include <QWidget>
#include <QSlider>

namespace Ui {
class ZoomSlider;
}

class ZoomSlider : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomSlider(QWidget *parent = 0);
    ~ZoomSlider();
    QSlider* slider();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_increaseButton_clicked();

    void on_decreaseButton_clicked();

private:
    Ui::ZoomSlider *ui;
};

#endif // ZOOMSLIDER_H
