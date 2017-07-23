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
