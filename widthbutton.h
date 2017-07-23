#ifndef WIDTHBUTTON_H
#define WIDTHBUTTON_H

#include <QToolButton>
#include <QSlider>

class MainWindow;

class WidthButton : public QToolButton {
    Q_OBJECT
public:
    WidthButton(MainWindow* parent);
    ~WidthButton();
    QSlider* widthSlider() const;

private :
    MainWindow* m_parent;
    QSlider* m_widthSlider;
    void setWidthSliderValue();
public slots:
    void setWidthText(int);
};

#endif // WIDTHBUTTON_H
