#include <QMenu>
#include <QWidgetAction>
#include "widthbutton.h"
#include "paintarea.h"
#include "mainwindow.h"

WidthButton::WidthButton(MainWindow* parent) : m_parent(parent), m_widthSlider(new QSlider)
{
    connect(this, &QToolButton::clicked, this, &WidthButton::setWidthSliderValue);
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setPopupMode(QToolButton::InstantPopup);
    auto menu = new QMenu();
    auto action = new QWidgetAction(menu);
    action->setDefaultWidget(m_widthSlider);
    menu->addAction(action);
    setMenu(menu);
    m_widthSlider->setMinimum(PaintArea::MIN_PEN_WIDTH);
    m_widthSlider->setMaximum(PaintArea::MAX_PEN_WIDTH);
    m_widthSlider->setMinimumSize(150, 15);
    m_widthSlider->setOrientation(Qt::Horizontal);
    //m_widthSlider->setWindowFlag(Qt::Popup);
    connect(m_widthSlider, &QSlider::valueChanged, this, &WidthButton::setWidthText);
    QIcon icon;
    icon.addFile(":/icons/lines.png");
    setIcon(icon);
    setWidthText(m_parent->paintArea()->pen().width());
}

WidthButton::~WidthButton()
{
    delete m_widthSlider;
}

QSlider* WidthButton::widthSlider() const
{
    return m_widthSlider;
}

void WidthButton::setWidthSliderValue()
{

    m_widthSlider->setValue(m_parent->paintArea()->pen().width());
}

void WidthButton::setWidthText(int value)
{
    setText(QStringLiteral("Pen width: ") + QString::number(value) + QStringLiteral(" px    "));
}
