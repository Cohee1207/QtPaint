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
