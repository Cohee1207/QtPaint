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

#include <QPalette>
#include <QMouseEvent>
#include "colorlabel.h"

QColor ColorLabel::color() const
{
    return m_color;
}

void ColorLabel::setColor(const QColor& color)
{
    m_color = color;
    setStyleSheet(QStringLiteral("border-style:inset;border-width:1px;border-color:#7A7A7A;")+QStringLiteral("background:") + m_color.name());
    setWindowOpacity(m_color.alpha() / 255);
}

void ColorLabel::openColorSelectionDialog()
{
    m_dialog->setOption(QColorDialog::ShowAlphaChannel);
    m_dialog->setCurrentColor(m_color);
    m_dialog->show();
}

ColorLabel::~ColorLabel()
{
    delete m_dialog;
}

QColorDialog* ColorLabel::dialog() const
{
    return m_dialog;
}

void ColorLabel::mouseReleaseEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton && m_clickable) {
        openColorSelectionDialog();
    }
}

ColorLabel::ColorLabel(QWidget* parent, const QColor& color, bool clickable) : QLabel(parent),
    m_dialog(new QColorDialog), m_clickable(clickable)
{
    connect(m_dialog, &QColorDialog::colorSelected, this, &ColorLabel::setColor);
    setColor(color);
    setText(QStringLiteral("         "));
}
