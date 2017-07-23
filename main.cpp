#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qApp->setStyleSheet( "QStatusBar::item { border: 0px}" );
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
