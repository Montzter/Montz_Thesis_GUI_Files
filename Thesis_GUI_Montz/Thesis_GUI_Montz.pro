#-------------------------------------------------
#
# Project created by QtCreator 2016-06-22T16:05:02
#
#-------------------------------------------------

QT       += core gui\
        serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Thesis_GUI_Montz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=
