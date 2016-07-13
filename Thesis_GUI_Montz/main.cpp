#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *window = new MainWindow;
    window->show();
    //window->SetSysTab(1);
    return a.exec();
}
