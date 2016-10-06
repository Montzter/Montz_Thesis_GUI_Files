/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSettings;
    QAction *actionDetect_System;
    QAction *actionClose;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCOM;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(695, 535);
        MainWindow->setMinimumSize(QSize(100, 100));
        MainWindow->setStyleSheet(QLatin1String("QMenuBar\n"
" {\n"
"	background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                         stop:0 #F7F7F7, stop:1 #E0E0E0);\n"
"	border-bottom: 1px outset grey;\n"
"	border-top: 1px outset grey;\n"
"	font-size: 16px;\n"
"}\n"
"\n"
"QMenuBar::item\n"
" {\n"
"	spacing: 3px;\n"
"	padding: 1px 4px;\n"
"	background: transparent;\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"QMenuBar::item:selected \n"
"{\n"
"	background: #A8A8A8;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"	background: #A8A8A8;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"	background-color: #D8D8D8;\n"
"	font-size: 16px;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"	padding: 2px 4px;\n"
"	background-color: #D8D8D8;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"	background-color: #E0E0E0;\n"
"	padding: 2px 4px;\n"
"	border: 1px inset gray;\n"
"	border-radius: 2px;\n"
"	color: #000000;\n"
"}\n"
"\n"
"QStatusBar\n"
"{\n"
"	border-top: 2px outset grey;\n"
"    background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                       "
                        "                  stop:0 #C7C7C7, stop:1 #E0E0E0);\n"
"}"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionDetect_System = new QAction(MainWindow);
        actionDetect_System->setObjectName(QStringLiteral("actionDetect_System"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 695, 24));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCOM = new QMenu(menuBar);
        menuCOM->setObjectName(QStringLiteral("menuCOM"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QLinearGradient gradient(0, 0, 0, 1);
        gradient.setSpread(QGradient::PadSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0, QColor(199, 199, 199, 255));
        gradient.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush1(gradient);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(227, 227, 227, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(100, 100, 100, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(133, 133, 133, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QLinearGradient gradient1(0, 0, 0, 1);
        gradient1.setSpread(QGradient::PadSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0, QColor(199, 199, 199, 255));
        gradient1.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush6(gradient1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        QLinearGradient gradient2(0, 0, 0, 1);
        gradient2.setSpread(QGradient::PadSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0, QColor(199, 199, 199, 255));
        gradient2.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush7(gradient2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush7);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QLinearGradient gradient3(0, 0, 0, 1);
        gradient3.setSpread(QGradient::PadSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0, QColor(199, 199, 199, 255));
        gradient3.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush9(gradient3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QLinearGradient gradient4(0, 0, 0, 1);
        gradient4.setSpread(QGradient::PadSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0, QColor(199, 199, 199, 255));
        gradient4.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush10(gradient4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush10);
        QLinearGradient gradient5(0, 0, 0, 1);
        gradient5.setSpread(QGradient::PadSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0, QColor(199, 199, 199, 255));
        gradient5.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush11(gradient5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush11);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        QLinearGradient gradient6(0, 0, 0, 1);
        gradient6.setSpread(QGradient::PadSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0, QColor(199, 199, 199, 255));
        gradient6.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush12(gradient6);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush12);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        QLinearGradient gradient7(0, 0, 0, 1);
        gradient7.setSpread(QGradient::PadSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0, QColor(199, 199, 199, 255));
        gradient7.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush13(gradient7);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush13);
        QLinearGradient gradient8(0, 0, 0, 1);
        gradient8.setSpread(QGradient::PadSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0, QColor(199, 199, 199, 255));
        gradient8.setColorAt(1, QColor(224, 224, 224, 255));
        QBrush brush14(gradient8);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush14);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush15(QColor(200, 200, 200, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush15);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        statusBar->setPalette(palette);
        statusBar->setLayoutDirection(Qt::LeftToRight);
        statusBar->setAutoFillBackground(false);
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCOM->menuAction());
        menuFile->addAction(actionSettings);
        menuFile->addAction(actionDetect_System);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuCOM->addAction(actionConnect);
        menuCOM->addAction(actionDisconnect);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindow", "Settings", 0));
#endif // QT_NO_TOOLTIP
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionDetect_System->setText(QApplication::translate("MainWindow", "Detect System", 0));
        actionDetect_System->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuCOM->setTitle(QApplication::translate("MainWindow", "Serial Port", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
