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
