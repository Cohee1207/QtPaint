#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include "paintarea.h"
#include "colorlabel.h"
#include "widthbutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    PaintArea* paintArea() const;

private slots:
    void on_actionOpen_file_triggered();

    void on_actionSave_file_triggered();

    void on_actionSelect_color_triggered();

    void on_actionIncrease_pen_width_triggered();

    void on_actionDecrease_pen_width_triggered();

    void on_actionShow_drawn_toggled(bool arg1);

    void on_actionNew_image_triggered();

    void on_actionPaste_triggered();

    void on_actionAbout_triggered();

    void on_actionClear_drawn_triggered();

    void on_actionCopy_triggered();

    void on_actionFlip_horizontal_triggered();

    void on_actionFlip_vertical_triggered();

    void on_actionRotate_left_triggered();

    void on_actionRotate_right_triggered();

private:
    QString m_fileName;
    QString m_filePath;
    QComboBox m_toolbox;
    Ui::MainWindow* ui;
    WidthButton* m_widthButton;
    ColorLabel m_strokeColorLabel;
    ColorLabel m_fillColorLabel;
    PaintArea* m_paintArea;
private:
    void closeEvent(QCloseEvent*) override;
    void setToolBox();
    void setStatusBar();
    bool saveExistingFile();
    bool saveNewFile();
    int confirmSaveAction();

};

#endif // MAINWINDOW_H
