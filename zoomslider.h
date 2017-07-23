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
