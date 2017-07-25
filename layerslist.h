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
