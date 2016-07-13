#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Dialog.h"
#include <QtWidgets>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void InitializeMainWindow();
    void InitializeStatusBar();
    void InitializeCentralWidget();
    int getStatusBarProgressBarValue();
    void setStatusBarVisibility(int status);
    void setRXBlink();
    void setTXBlink();
    void setSysStatusValText(int lblID,char LabelString[]);
    void setSysTabLabels(int LabelID, int rowNum, char StatString[], char StatVal[]);
    void setSysTabHeader(int HeaderID, int rowNum, char HeaderString[]);
    void setupSysPensandBrushes();
    void setSysDiagramRect(int RectID, int x, int y, int w, int h, QPen pen, QBrush brush);
    void changeSysDiagramRect(int RectID, int BrushID);
    void setSysDiagramRectGradient(int RectID, char RGB1[], char RGB2[]);
    void setSysDiagramEli(int ElipseID, int x, int y, int w, int h, QPen pen, QBrush brush);
    void changeSysDiagramEli(int ElipseID, int BrushID);
    void setSysDiagramEliGradient(int ElipseID, char RGB1[], char RGB2[]);
    void setSysDiagramLine(int LineID, int x1, int y1, int x2, int y2, QPen pen);
    void changeSysDiagramLine(int LineID, int x1, int y1, int x2, int y2, int PenID);
    void SetSysTab(int sysID);//Setup system tab based on sysID from system
    void clearSystemTab();
    void resizeEvent (QResizeEvent * event );

    ~MainWindow();

signals:
    void showSettings();

public slots:
    void UART_RX_Message(char RX_MSG[]);
    void setStatusBarText(char LabelString[]);
    void refreshStatusBarText();
    void setStatusBarProgressBarValue(int PBVal);

private slots:
    void on_actionClose_triggered();
    void on_actionSettings_triggered();
    void on_actionDetect_System_triggered();
    void resetRXIndicator();
    void resetTXIndicator();
    void refitScene();

    //void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    Dialog *settings;
    int sysID; //0:No id, 1:MSP430/FPGA 2:R_Pi 3:Other System?


    //Objects for main widget
    QWidget *cWidget;   //Central Widget containing the TabsWidget
    QVBoxLayout *cvLayout; //Central layout holding Tab widget
    QTabWidget *cwTabWidget;    //Tab widget
    QWidget *sysTabBorder;  //Border Widget for system tab
    QVBoxLayout *sysTabBorderLayout;
    QSplitter *sysSplitter; //Splitter for system tab
    QWidget *imgTabBorder;  //Border Widget for image tab
    QVBoxLayout *imgTabBorderLayout;
    QSplitter *imgSplitter; //Splitter for image tab

        //System Tab Widgets
            //Left collumn of system tab splitter
            QWidget *sysStatusW;
            QVBoxLayout *sysStatusVLayout;
            QLabel *sysStatusLbl;
            QWidget *sysStatusLowerW;
            QGridLayout *sysStatusGridLayout;
                //MSP430_FPGA system status objects
                QLabel *sysStatusHeader1;//
                QLabel *sysStatusHeader2;//
                QLabel *sysStatusHeader3;//
                QLabel *sysStatusHeader4;//

                QFrame *sysStatusLine1;//
                QFrame *sysStatusLine2;//
                QFrame *sysStatusLine3;//
                QFrame *sysStatusLine4;//

                QLabel *sysStatusStat1;//
                QLabel *sysStatusStat2;//
                QLabel *sysStatusStat3;//
                QLabel *sysStatusStat4;//
                QLabel *sysStatusStat5;//
                QLabel *sysStatusStat6;//
                QLabel *sysStatusStat7;//
                QLabel *sysStatusStat8;//
                QLabel *sysStatusStat9;//
                QLabel *sysStatusStat10;//
                QLabel *sysStatusStat11;//
                QLabel *sysStatusStat12;//
                QLabel *sysStatusStat13;//
                QLabel *sysStatusStat14;//
                QLabel *sysStatusStat15;//


                QLabel *sysStatusVal1;//
                QLabel *sysStatusVal2;//
                QLabel *sysStatusVal3;//
                QLabel *sysStatusVal4;//
                QLabel *sysStatusVal5;//
                QLabel *sysStatusVal6;//
                QLabel *sysStatusVal7;//
                QLabel *sysStatusVal8;//
                QLabel *sysStatusVal9;//
                QLabel *sysStatusVal10;//
                QLabel *sysStatusVal11;//
                QLabel *sysStatusVal12;//
                QLabel *sysStatusVal13;//
                QLabel *sysStatusVal14;//
                QLabel *sysStatusVal15;//

                QWidget *sysStatusFiller;//


            //Central collumn of system tab splitter
            QWidget *sysDiagramW;
            QVBoxLayout *sysDiagramVLayout;
            QLabel *sysDiagramLbl;
            QGraphicsView *sysDiagramDraw;
            QGraphicsScene *sysDiagramScene;
            QRectF sysDiagramSceneBounds;
                QPixmap *MSP430_FPGA_System_Diagram;//

                QBrush *greenBrush;
                QBrush *redBrush;
                QBrush *blueBrush;
                QBrush *yellowBrush;

                QPen *blackPen;
                QPen *greenPen;
                QPen *redPen;

                QGraphicsRectItem *sysDiagramRect1;
                QGraphicsRectItem *sysDiagramRect2;
                QGraphicsRectItem *sysDiagramRect3;
                QGraphicsRectItem *sysDiagramRect4;
                QGraphicsRectItem *sysDiagramRect5;
                QGraphicsRectItem *sysDiagramRect6;
                QGraphicsRectItem *sysDiagramRect7;
                QGraphicsRectItem *sysDiagramRect8;
                QGraphicsRectItem *sysDiagramRect9;
                QGraphicsRectItem *sysDiagramRect10;
                QGraphicsRectItem *sysDiagramRect11;

                QLinearGradient *sysDiagramRect1Gradient;
                QLinearGradient *sysDiagramRect2Gradient;
                QLinearGradient *sysDiagramRect3Gradient;
                QLinearGradient *sysDiagramRect4Gradient;
                QLinearGradient *sysDiagramRect5Gradient;
                QLinearGradient *sysDiagramRect6Gradient;
                QLinearGradient *sysDiagramRect7Gradient;
                QLinearGradient *sysDiagramRect8Gradient;
                QLinearGradient *sysDiagramRect9Gradient;
                QLinearGradient *sysDiagramRect10Gradient;
                QLinearGradient *sysDiagramRect11Gradient;


                QGraphicsLineItem *sysDiagramLine1;

                QGraphicsEllipseItem *sysDiagramEllipse1;

                QRadialGradient *sysDiagramEllipse1Gradient;

            //Right collumn of system tab splitter
            QWidget *sysCommandsW;
            QVBoxLayout *sysCommandsVLayout;
            QLabel *sysCommandsLbl;
            QWidget *sysCommandsSubWidget;


        //Images Tab Widgets
            QWidget *cImagesTab;
            QGridLayout *imgGridLayout;
            QLabel *imgList;
            QLabel *imgIMG;
            QLabel *imgStats;




    //Objects of status bar
    QString statusBar_Text;
    QProgressBar *statusBar_ProgressBar;
    QLabel *statusBar_RXLabel;
    QLabel *statusBar_RXIndicator;
    QTimer *statusBar_RXI_Timer;
    QLabel *statusBar_TXLabel;
    QLabel *statusBar_TXIndicator;
    QTimer *statusBar_TXI_Timer;
};

#endif // MAINWINDOW_H
