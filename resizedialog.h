#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class ResizeDialog;
}

class ResizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeDialog(QWidget *parent = 0);
    ~ResizeDialog();

private:
    Ui::ResizeDialog *ui;
};

#endif // RESIZEDIALOG_H
