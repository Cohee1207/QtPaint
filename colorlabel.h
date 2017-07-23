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
