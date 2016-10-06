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
    dialog.cpp \
    myuart.cpp \
    orientationdialog.cpp \
    orbitalanimationwidget.cpp \
    colortables.cpp \
    imgdatreader.cpp \
    mycustomscene.cpp \
    colorkey.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    myuart.h \
    orientationdialog.h \
    orbitalanimationwidget.h \
    imgdatreader.h \
    mycustomscene.h \
    colorkey.h

FORMS    += mainwindow.ui \
    dialog.ui \
    orientationdialog.ui \
    colorkey.ui

RC_FILE = myapp.rc

DISTFILES +=

RESOURCES += \
    myfiles.qrc
