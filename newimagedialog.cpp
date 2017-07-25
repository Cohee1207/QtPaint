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

#include "newimagedialog.h"
#include "ui_newimagedialog.h"

#include "paintarea.h"

NewImageDialog::NewImageDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewImageDialog)
{
    ui->setupUi(this);
    ui->heightSpinBox->setMaximum(PaintArea::MAX_IMAGE_SIZE);
    ui->widthSpinBox->setMaximum(PaintArea::MAX_IMAGE_SIZE);
    ui->heightSpinBox->setMinimum(PaintArea::MIN_IMAGE_SIZE);
    ui->heightSpinBox->setValue(PaintArea::DEFAULT_HEIGHT);
    ui->widthSpinBox->setValue(PaintArea::DEFAULT_WIDTH);
    ui->heightSpinBox->setMinimum(PaintArea::MIN_IMAGE_SIZE);
}

NewImageDialog::~NewImageDialog()
{
    delete ui;
}

int NewImageDialog::width()
{
    return ui->widthSpinBox->value();
}

int NewImageDialog::height()
{
    return ui->heightSpinBox->value();
}

QColor NewImageDialog::color()
{
    return ui->colorLabel->color();
}
