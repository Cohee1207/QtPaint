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
    setStyleSheet(QStringLiteral("border-style:inset;border-width:1px;border-color:#999999;")+QStringLiteral("background:") + m_color.name());
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
