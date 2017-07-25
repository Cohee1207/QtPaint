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
