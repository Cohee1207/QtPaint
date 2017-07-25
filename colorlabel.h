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

#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <QColorDialog>

class ColorLabel : public QLabel {
    Q_OBJECT
private:
    QColorDialog* m_dialog;
    QString toCssColor(const QColor&);
    QColor m_color;
    bool m_clickable;
    void mouseReleaseEvent(QMouseEvent* ev) override;
public slots:
    void setColor(const QColor& color);
public:
    ColorLabel(QWidget* parent = nullptr, const QColor& color = QColor(Qt::white), bool clickable = true);
    QColor color() const;
    void openColorSelectionDialog();
    ~ColorLabel();
    QColorDialog* dialog() const;
};

#endif // COLORLABEL_H
