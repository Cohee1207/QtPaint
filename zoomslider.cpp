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
