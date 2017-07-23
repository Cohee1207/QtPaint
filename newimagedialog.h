#ifndef NEWIMAGEDIALOG_H
#define NEWIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class NewImageDialog;
}

class NewImageDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewImageDialog(QWidget* parent = 0);
    ~NewImageDialog();
    int width();
    int height();
    QColor color();

private:
    Ui::NewImageDialog* ui;
};

#endif // NEWIMAGEDIALOG_H
