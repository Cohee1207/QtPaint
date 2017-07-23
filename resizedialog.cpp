#include "resizedialog.h"
#include "ui_resizedialog.h"

ResizeDialog::ResizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeDialog)
{
    ui->setupUi(this);
}

ResizeDialog::~ResizeDialog()
{
    delete ui;
}
