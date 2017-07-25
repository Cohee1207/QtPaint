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

#include "zoomslider.h"
#include "ui_zoomslider.h"

static const int BUTTON_STEP = 10;

ZoomSlider::ZoomSlider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomSlider)
{
    ui->setupUi(this);
}

ZoomSlider::~ZoomSlider()
{
    delete ui;
}

QSlider *ZoomSlider::slider()
{
    return ui->horizontalSlider;
}

void ZoomSlider::on_horizontalSlider_valueChanged(int value)
{
    ui->percentLabel->setText(QString::number(value) + QStringLiteral("%"));
}

void ZoomSlider::on_increaseButton_clicked()
{
    auto value = ui->horizontalSlider->value();
    value += BUTTON_STEP;
    ui->horizontalSlider->setValue(value);
}

void ZoomSlider::on_decreaseButton_clicked()
{
    auto value = ui->horizontalSlider->value();
    value -= BUTTON_STEP;
    ui->horizontalSlider->setValue(value);
}
