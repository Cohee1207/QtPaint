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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QDockWidget>
#include "paintarea.h"
#include "colorlabel.h"
#include "widthbutton.h"
#include "layerslist.h"

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

    void on_actionNew_image_triggered();

    void on_actionPaste_triggered();

    void on_actionAbout_triggered();

    void on_actionCopy_triggered();

    void on_actionFlip_horizontal_triggered();

    void on_actionFlip_vertical_triggered();

    void on_actionRotate_left_triggered();

    void on_actionRotate_right_triggered();

    void on_actionLayers_triggered(bool checked);

private:
    QString m_fileName;
    LayersList* m_layersList;
    QString m_filePath;
    QComboBox m_toolbox;
    QDockWidget m_dock;
    Ui::MainWindow* ui;
    WidthButton* m_widthButton;
    ColorLabel m_strokeColorLabel;
    ColorLabel m_fillColorLabel;
    PaintArea* m_paintArea;
private:
    void closeEvent(QCloseEvent*) override;
    void setToolBox();
    void setStatusBar();
    void setDock();
    bool saveExistingFile();
    bool saveNewFile();
    int confirmSaveAction();

};

#endif // MAINWINDOW_H
