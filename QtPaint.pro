#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T09:49:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtPaint
TEMPLATE = app

L#IBS += -lopengl32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    paintarea.cpp \
    colorlabel.cpp \
    newimagedialog.cpp \
    resizedialog.cpp \
    brushtool.cpp \
    erasertool.cpp \
    linetool.cpp \
    rectangletool.cpp \
    widthbutton.cpp \
    floodfilltool.cpp \
    ellipsetool.cpp \
    layer.cpp \
    paintwidget.cpp \
    zoomslider.cpp \
    layerslist.cpp

HEADERS += \
        mainwindow.h \
    paintarea.h \
    colorlabel.h \
    newimagedialog.h \
    resizedialog.h \
    painttool.h \
    brushtool.h \
    erasertool.h \
    linetool.h \
    rectangletool.h \
    widthbutton.h \
    floodfilltool.h \
    ellipsetool.h \
    layer.h \
    paintwidget.h \
    zoomslider.h \
    layerslist.h \
    paintevent.h

FORMS += \
        mainwindow.ui \
    newimagedialog.ui \
    resizedialog.ui \
    zoomslider.ui \
    layerslist.ui

RESOURCES += \
    resources.qrc
