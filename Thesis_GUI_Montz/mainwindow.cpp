#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QtWidgets>

//MainWindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    InitializeMainWindow();
    InitializeCentralWidget();
    InitializeStatusBar();


    //SetSysTab(1);
    //changeSysDiagramRect(1,4);
    //changeSysDiagramEli(1,4);
    //changeSysDiagramLine(1, 212, 31, 244, 31, 2);
    //changeSysDiagramLine(1, 212, 30, 250, 15, 3);
    //setSysDiagramRectGradient(1, "#FF0000", "#760000");
    //setSysDiagramRectGradient(1, "#8E0E00", "1F1C18");

    //clearSystemTab();
    setStatusBarText("Verify settings and connect to system.");
}

//MainWindow destructor
MainWindow::~MainWindow()
{
    delete ui;
}
//****************************************************//
//*********Initialization Functions*******************//
//****************************************************//
//Initialization of the MainWindow object
void MainWindow::InitializeMainWindow()
{
    //Set Main Window title
    setWindowTitle("Thesis GUI");

    //Set Main Window minimum size
    setMinimumWidth(1070);
    setMinimumHeight(800);

    ui->actionDisconnect->setEnabled(false);
    ui->actionDetect_System->setEnabled(false);

    //Set systemID to 0
    sysID = 0;
}

//Initialization of MainWindows central widget
void MainWindow::InitializeCentralWidget()
{
    //Main widget containing Tab widget and vboxlayout
    cWidget = new QWidget(this);
    cvLayout = new QVBoxLayout;
    cWidget->setLayout(cvLayout);
    setCentralWidget(cWidget);

    //Main Tab widget of Main Window central widget
    cwTabWidget = new QTabWidget(this);
    cvLayout->addWidget(cwTabWidget);

    //Splitter for System tab
    sysSplitter = new QSplitter(this);
    sysSplitter->setStyleSheet("background-color: #000000");
    sysSplitter->setHandleWidth(5);
    sysSplitter->setChildrenCollapsible(false);

    //Splitter for Images tab
    imgSplitter = new QSplitter(this);

    //Borders for tabs
    sysTabBorder = new QWidget(this);
    sysTabBorderLayout = new QVBoxLayout;
    sysTabBorder->setLayout(sysTabBorderLayout);
    sysTabBorderLayout->addWidget(sysSplitter);
    sysTabBorder->setStyleSheet("background-color: #FFFFFF");
    imgTabBorder = new QWidget(this);
    imgTabBorderLayout = new QVBoxLayout;
    imgTabBorder->setLayout(imgTabBorderLayout);
    imgTabBorderLayout->addWidget(imgSplitter);

    //Add Splitters as tabs
    cwTabWidget->addTab(sysTabBorder,tr("System"));
    cwTabWidget->addTab(imgTabBorder,tr("Images"));

    //Left collumn of system tab splitter (System Status)
    sysStatusW = new QWidget(this);
    sysStatusW->setMaximumWidth(320);
    sysStatusW->setMinimumWidth(320);
    sysStatusVLayout = new QVBoxLayout;
    sysStatusLbl = new QLabel(this);
    sysStatusLbl->setMinimumHeight(20);
    sysStatusLbl->setMaximumHeight(20);
    sysStatusLbl->setText("System Status");
    sysStatusLbl->setStyleSheet("background-color: #FFFFFF; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysStatusLowerW = new QWidget(this);
    sysStatusLowerW->setStyleSheet("QWidget{background-color: #FFFFFF;}QLabel{background-color: #FFFFFF; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    sysStatusGridLayout = new QGridLayout;
    sysStatusLowerW->setLayout(sysStatusGridLayout);
    sysStatusLowerW->setMinimumWidth(200);//***********
    sysStatusVLayout->addWidget(sysStatusLbl);
    sysStatusVLayout->addWidget(sysStatusLowerW);
    sysStatusVLayout->setContentsMargins(2,2,0,2);
    sysStatusW->setLayout(sysStatusVLayout);
    sysSplitter->addWidget(sysStatusW);

    //Central collumn of system tab splitter (System Status Diagram)
    sysDiagramW = new QWidget(this);
    sysDiagramW->setMinimumWidth(420);
    sysDiagramVLayout = new QVBoxLayout;
    sysDiagramLbl = new QLabel(this);
    sysDiagramLbl->setMinimumHeight(20);
    sysDiagramLbl->setMaximumHeight(20);
    sysDiagramLbl->setText("System Status Diagram");
    sysDiagramLbl->setStyleSheet("background-color: #FFFFFF; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysDiagramDraw = new QGraphicsView(this);
    sysDiagramDraw->setStyleSheet("background-color: #FFFFFF");
    sysDiagramScene = new QGraphicsScene(this);
    sysDiagramDraw->setScene(sysDiagramScene);
    sysDiagramVLayout->addWidget(sysDiagramLbl);
    sysDiagramVLayout->addWidget(sysDiagramDraw);
    sysDiagramVLayout->setContentsMargins(0,2,0,2);
    sysDiagramW->setLayout(sysDiagramVLayout);
    sysSplitter->addWidget(sysDiagramW);


    //sysDiagramDraw->setSceneRect(0,0);

    //Right collumn of system tab splitter (commands)
    sysCommandsW = new QWidget(this);
    sysCommandsW->setMinimumWidth(200);
    sysCommandsVLayout = new QVBoxLayout;
    sysCommandsLbl = new QLabel(this);
    sysCommandsLbl->setMinimumHeight(20);
    sysCommandsLbl->setMaximumHeight(20);
    sysCommandsLbl->setText("Commands");
    sysCommandsLbl->setStyleSheet("background-color: #FFFFFF; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysCommandsSubWidget = new QWidget(this);
    sysCommandsSubWidget->setStyleSheet("background-color: #FFFFFF");
    sysCommandsVLayout->addWidget(sysCommandsLbl);
    sysCommandsVLayout->addWidget(sysCommandsSubWidget);
    sysCommandsVLayout->setContentsMargins(0,2,2,2);
    sysCommandsW->setLayout(sysCommandsVLayout);
    sysSplitter->addWidget(sysCommandsW);
    cwTabWidget->setStyleSheet("QTabBar::tab {min-width: 20ex;font-size: 16px;}");
}

//Initialization of the MainWindows status bar
void MainWindow::InitializeStatusBar()
{
    //Create statusBar objects and vars
    statusBar_ProgressBar = new QProgressBar(this);
    statusBar_RXLabel = new QLabel(this);
    statusBar_RXIndicator = new QLabel(this);
    statusBar_RXI_Timer = new QTimer(this);
    statusBar_TXLabel = new QLabel(this);
    statusBar_TXIndicator = new QLabel(this);
    statusBar_TXI_Timer = new QTimer(this);

    //Set statusBar message
    setStatusBarText("COM Port Disconnected");
    connect(ui->statusBar,SIGNAL(messageChanged(QString)),this,SLOT(refreshStatusBarText()));

    //Setup statusBar Progress Bar
    statusBar_ProgressBar->setMinimum(0);
    statusBar_ProgressBar->setMaximum(100);
    setStatusBarProgressBarValue(0);

    //Setup statusBar RX text
    statusBar_RXLabel->setText("RX: ");

    //Setup statusBar RX Indicator
    statusBar_RXIndicator->setText("          ");
    statusBar_RXIndicator->setStyleSheet("QLabel{background-color:rgb(130,0,0);\
                                                 border: 2px inset grey}");

    //Setup statusBar RX Indicator timer
    statusBar_RXI_Timer->setSingleShot(true);
    statusBar_RXI_Timer->setInterval(400);
    connect(statusBar_RXI_Timer,SIGNAL(timeout()),
            this,SLOT(resetRXIndicator()));

    //Setup statusBar TX text
    statusBar_TXLabel->setText("TX: ");

    //Setup statusBar TX Indicator
    statusBar_TXIndicator->setText("          ");
    statusBar_TXIndicator->setStyleSheet("QLabel {background-color:rgb(0,130,0);\
                                                  border: 2px inset grey}");

    //Setup statusBar TX Indicator timer
    statusBar_TXI_Timer->setSingleShot(true);
    statusBar_TXI_Timer->setInterval(300);
    connect(statusBar_TXI_Timer,SIGNAL(timeout()),
            this,SLOT(resetTXIndicator()));

    //Set statusbar to 'disconnected' visibility
    setStatusBarVisibility(0);
    //setStatusBarVisibility_Disconnected();

    //Add widgets to statusBar
    ui->statusBar->addPermanentWidget(statusBar_ProgressBar);
    ui->statusBar->addPermanentWidget(statusBar_RXLabel);
    ui->statusBar->addPermanentWidget(statusBar_RXIndicator);
    ui->statusBar->addPermanentWidget(statusBar_TXLabel);
    ui->statusBar->addPermanentWidget(statusBar_TXIndicator);
}

//****************************************************//
//*************Status Bar Functions*******************//
//****************************************************//

//SLOT sets the status bar message to input char array
void MainWindow::setStatusBarText(char LabelString[])
{
    statusBar_Text = QString::fromLocal8Bit(LabelString);
    ui->statusBar->showMessage(statusBar_Text);
}

//SLOT refreshes the status bar text to the saved value
//  *used to prevent unintentional erasing by main window
void MainWindow::refreshStatusBarText()
{
    if(ui->statusBar->currentMessage() != statusBar_Text)
        ui->statusBar->showMessage(statusBar_Text);
}

//Get the current value of the status bars progress bar
int MainWindow::getStatusBarProgressBarValue()
{
    return statusBar_ProgressBar->value();
}

//Set the value of the status bars progress bar
void MainWindow::setStatusBarProgressBarValue(int PBVal)
{
    statusBar_ProgressBar->setValue(PBVal);
}

//Set the status bars widgets visibility
void MainWindow::setStatusBarVisibility(int status)
{
    switch(status)
    {
        case 0://Disconnected
        {
            statusBar_ProgressBar->setVisible(false);
            statusBar_RXLabel->setVisible(false);
            statusBar_RXIndicator->setVisible(false);
            statusBar_TXLabel->setVisible(false);
            statusBar_TXIndicator->setVisible(false);
            break;
        }
        case 1://Connected
        {
            statusBar_ProgressBar->setVisible(false);
            statusBar_RXLabel->setVisible(true);
            statusBar_RXIndicator->setVisible(true);
            statusBar_TXLabel->setVisible(true);
            statusBar_TXIndicator->setVisible(true);
            break;
        }
        case 2://RXing_IMG
        {
            statusBar_ProgressBar->setVisible(true);
            statusBar_RXLabel->setVisible(true);
            statusBar_RXIndicator->setVisible(true);
            statusBar_TXLabel->setVisible(true);
            statusBar_TXIndicator->setVisible(true);
            break;
        }
        default: break;
    }
}

//****************************************************//
//***********Blinking RX/TX Functions*****************//
//****************************************************//

//Start a blink of the RX indicator
void MainWindow::setRXBlink()
{
    statusBar_RXIndicator->setStyleSheet("QLabel{background-color:rgb(255,0,0);\
                                                 border: 2px inset grey}");
    statusBar_RXI_Timer->start();
}

//Turn off the RX indicator, signaled by RXI timer
void MainWindow::resetRXIndicator()
{
    statusBar_RXIndicator->setStyleSheet("QLabel{background-color:rgb(130,0,0);\
                                                 border: 2px inset grey}");
}

//Start a blink of the TX indicator
void MainWindow::setTXBlink()
{
    statusBar_TXIndicator->setStyleSheet("QLabel{background-color:rgb(0,255,0);\
                                                 border: 2px inset grey}");
    statusBar_TXI_Timer->start();
}

//Turn off the TX indicator, signaled by TXI timer
void MainWindow::resetTXIndicator()
{
    statusBar_TXIndicator->setStyleSheet("QLabel {background-color:rgb(0,130,0);\
                                                  border: 2px inset grey}");
}

//****************************************************//
//************System Tab Functions*****************//
//****************************************************//

//Setup the system tab based on the system ID
void MainWindow::SetSysTab(int systemID)
{
    clearSystemTab();
    sysID = systemID;
    setupSysPensandBrushes();
    switch(sysID)
    {
    case 0: //No system id given
    {

        break;
    }
    case 1: //MSP430/FPGA system
    {
        setSysTabHeader(1,0,"<B>State:</B>");

        setSysTabLabels(1,2,"System State:","A");

        setSysTabHeader(2,3,"<B>Power</B>");

        setSysTabLabels(2,5,"Relay:","Open");
        setSysTabLabels(3,6,"5 V Regulator:","Off");
        setSysTabLabels(4,7,"3.3 V Regulator(MSP430):","On");
        setSysTabLabels(5,8,"3.3 V Regulator(Quark/S.Flash):","Off");

        setSysTabHeader(3,9,"<B>Components</B>");

        setSysTabLabels(6,11,"MSP430:","LPM");
        setSysTabLabels(7,12,"FPGA:","Off");
        setSysTabLabels(8,13,"Quark:","Off");
        setSysTabLabels(9,14,"S.Flash:","Off");
        setSysTabLabels(10,15,"Servo:","Off");
        setSysTabLabels(11,16,"Servo Position:","Black Body");

        setSysTabHeader(4,17,"<B>Signals</B>");

        setSysTabLabels(12,19,"5 V SHDN:","GND");
        setSysTabLabels(13,20,"3.3 V SHDN(Quark/S.Flash):","GND");
        setSysTabLabels(14,21,"QUARK SHDN:","GND");
        setSysTabLabels(15,22,"Servo PWM Signal:","Off");

        sysStatusFiller = new QWidget(sysStatusLowerW);
        sysStatusGridLayout->addWidget(sysStatusFiller,23,0);
        sysStatusGridLayout->setRowStretch(23,11000);

        MSP430_FPGA_System_Diagram = new QPixmap(".\\MSP430_FPGA_System.png");
        sysDiagramScene->addPixmap(*MSP430_FPGA_System_Diagram);

        setSysDiagramRect(1,187,107,81,36,*blackPen,*redBrush);
        setSysDiagramRectGradient(1, "#DD0000", "#990000");

        setSysDiagramRect(2,187,211,81,32,*blackPen,*greenBrush);
        setSysDiagramRectGradient(2, "#00DD00", "#009900");

        setSysDiagramRect(3,187,320,81,32,*blackPen,*redBrush);
        setSysDiagramRectGradient(3, "#DD0000", "#990000");

        setSysDiagramRect(4,331,3,55,55,*blackPen,*redBrush);
        setSysDiagramRectGradient(4, "#DD0000", "#990000");

        setSysDiagramRect(5,331,195,55,55,*blackPen,*blueBrush);
        setSysDiagramRectGradient(5, "#0000DD", "#000099");

        setSysDiagramRect(6,331,318,42,28,*blackPen,*redBrush);
        setSysDiagramRectGradient(6, "#DD0000", "#990000");

        setSysDiagramRect(7,331,386,55,28,*blackPen,*redBrush);
        setSysDiagramRectGradient(7, "#DD0000", "#990000");

        setSysDiagramEli(1,331,89,64,64,*blackPen,*redBrush);
        setSysDiagramEliGradient(1, "#DD0000", "#990000");

        setSysDiagramLine(1,212,30,250,15,*redPen);

        //Key
        //On
        setSysDiagramRect(8,137,485,63,19,*blackPen,*greenBrush);
        setSysDiagramRectGradient(8, "#00DD00", "#009900");
        //Off
        setSysDiagramRect(9,320,485,63,19,*blackPen,*redBrush);
        setSysDiagramRectGradient(9, "#DD0000", "#990000");
        //AM
        setSysDiagramRect(10,137,525,63,19,*blackPen,*yellowBrush);
        setSysDiagramRectGradient(10, "#DDDD00", "#999900");
        //LPM
        setSysDiagramRect(11,320,525,63,19,*blackPen,*blueBrush);
        setSysDiagramRectGradient(11, "#0000DD", "#000099");

        break;
    }
    case 2: //R_Pi system
    {

        break;
    }
    case 3: //Other systems
    {

        break;
    }
    default: break; //Error
    }
}

//Clears the system tab based on the system ID
void MainWindow::clearSystemTab()
{
    switch(sysID)
    {
        case 0: break; //No id;
        case 1: //MSP430/FPGA;
        {
            sysStatusGridLayout->removeWidget(sysStatusHeader1);delete(sysStatusHeader1);
            sysStatusGridLayout->removeWidget(sysStatusHeader2);delete(sysStatusHeader2);
            sysStatusGridLayout->removeWidget(sysStatusHeader3);delete(sysStatusHeader3);
            sysStatusGridLayout->removeWidget(sysStatusHeader4);delete(sysStatusHeader4);
            sysStatusGridLayout->removeWidget(sysStatusLine1);delete(sysStatusLine1);
            sysStatusGridLayout->removeWidget(sysStatusLine2);delete(sysStatusLine2);
            sysStatusGridLayout->removeWidget(sysStatusLine3);delete(sysStatusLine3);
            sysStatusGridLayout->removeWidget(sysStatusLine4);delete(sysStatusLine4);
            sysStatusGridLayout->removeWidget(sysStatusStat1);delete(sysStatusStat1);
            sysStatusGridLayout->removeWidget(sysStatusVal1);delete(sysStatusVal1);
            sysStatusGridLayout->removeWidget(sysStatusStat2);delete(sysStatusStat2);
            sysStatusGridLayout->removeWidget(sysStatusVal2);delete(sysStatusVal2);
            sysStatusGridLayout->removeWidget(sysStatusStat3);delete(sysStatusStat3);
            sysStatusGridLayout->removeWidget(sysStatusVal3);delete(sysStatusVal3);
            sysStatusGridLayout->removeWidget(sysStatusStat4);delete(sysStatusStat4);
            sysStatusGridLayout->removeWidget(sysStatusVal4);delete(sysStatusVal4);
            sysStatusGridLayout->removeWidget(sysStatusStat5);delete(sysStatusStat5);
            sysStatusGridLayout->removeWidget(sysStatusVal5);delete(sysStatusVal5);
            sysStatusGridLayout->removeWidget(sysStatusStat6);delete(sysStatusStat6);
            sysStatusGridLayout->removeWidget(sysStatusVal6);delete(sysStatusVal6);
            sysStatusGridLayout->removeWidget(sysStatusStat7);delete(sysStatusStat7);
            sysStatusGridLayout->removeWidget(sysStatusVal7);delete(sysStatusVal7);
            sysStatusGridLayout->removeWidget(sysStatusStat8);delete(sysStatusStat8);
            sysStatusGridLayout->removeWidget(sysStatusVal8);delete(sysStatusVal8);
            sysStatusGridLayout->removeWidget(sysStatusStat9);delete(sysStatusStat9);
            sysStatusGridLayout->removeWidget(sysStatusVal9);delete(sysStatusVal9);
            sysStatusGridLayout->removeWidget(sysStatusStat10);delete(sysStatusStat10);
            sysStatusGridLayout->removeWidget(sysStatusVal10);delete(sysStatusVal10);
            sysStatusGridLayout->removeWidget(sysStatusStat11);delete(sysStatusStat11);
            sysStatusGridLayout->removeWidget(sysStatusVal11);delete(sysStatusVal11);
            sysStatusGridLayout->removeWidget(sysStatusStat12);delete(sysStatusStat12);
            sysStatusGridLayout->removeWidget(sysStatusVal12);delete(sysStatusVal12);
            sysStatusGridLayout->removeWidget(sysStatusStat13);delete(sysStatusStat13);
            sysStatusGridLayout->removeWidget(sysStatusVal13);delete(sysStatusVal13);
            sysStatusGridLayout->removeWidget(sysStatusStat14);delete(sysStatusStat14);
            sysStatusGridLayout->removeWidget(sysStatusVal14);delete(sysStatusVal14);
            sysStatusGridLayout->removeWidget(sysStatusStat15);delete(sysStatusStat15);
            sysStatusGridLayout->removeWidget(sysStatusVal15);delete(sysStatusVal15);
            sysStatusGridLayout->removeWidget(sysStatusFiller);delete(sysStatusFiller);
            sysDiagramScene->clear();
            break;
        }
        case 2:
        {

            break;//R_Pi
        }
        case 3:
        {

            break;//Other System?
        }
        default: break;//Error
    }
}

//Creates and sets the system status headers and lines
void MainWindow::setSysTabHeader(int HeaderID, int rowNum, char HeaderString[])
{
    switch(HeaderID)
    {
        case 1:
        {
            sysStatusHeader1 = new QLabel(sysStatusLowerW);
            sysStatusHeader1->setText(HeaderString);
            sysStatusHeader1->setStyleSheet("qproperty-alignment: AlignLeft;");
            sysStatusGridLayout->addWidget(sysStatusHeader1,rowNum,0,1,2);

            sysStatusLine1 = new QFrame(sysStatusLowerW);
            sysStatusLine1->setFrameShape(QFrame::HLine);
            sysStatusLine1->setFrameShadow(QFrame::Sunken);
            sysStatusGridLayout->addWidget(sysStatusLine1,rowNum+1,0,1,2);
            break;
        }
        case 2:
        {
            sysStatusHeader2 = new QLabel(sysStatusLowerW);
            sysStatusHeader2->setText(HeaderString);
            sysStatusHeader2->setStyleSheet("qproperty-alignment: AlignLeft;");
            sysStatusGridLayout->addWidget(sysStatusHeader2,rowNum,0,1,2);

            sysStatusLine2 = new QFrame(sysStatusLowerW);
            sysStatusLine2->setFrameShape(QFrame::HLine);
            sysStatusLine2->setFrameShadow(QFrame::Sunken);
            sysStatusGridLayout->addWidget(sysStatusLine2,rowNum+1,0,1,2);
            break;
        }
        case 3:
        {
            sysStatusHeader3 = new QLabel(sysStatusLowerW);
            sysStatusHeader3->setText(HeaderString);
            sysStatusHeader3->setStyleSheet("qproperty-alignment: AlignLeft;");
            sysStatusGridLayout->addWidget(sysStatusHeader3,rowNum,0,1,2);

            sysStatusLine3 = new QFrame(sysStatusLowerW);
            sysStatusLine3->setFrameShape(QFrame::HLine);
            sysStatusLine3->setFrameShadow(QFrame::Sunken);
            sysStatusGridLayout->addWidget(sysStatusLine3,rowNum+1,0,1,2);
            break;
        }
        case 4:
        {
            sysStatusHeader4 = new QLabel(sysStatusLowerW);
            sysStatusHeader4->setText(HeaderString);
            sysStatusHeader4->setStyleSheet("qproperty-alignment: AlignLeft;");
            sysStatusGridLayout->addWidget(sysStatusHeader4,rowNum,0,1,2);

            sysStatusLine4 = new QFrame(sysStatusLowerW);
            sysStatusLine4->setFrameShape(QFrame::HLine);
            sysStatusLine4->setFrameShadow(QFrame::Sunken);
            sysStatusGridLayout->addWidget(sysStatusLine4,rowNum+1,0,1,2);
            break;
        }
        default: break;
    }
}

//Creates and sets the system status stat and val labels
void MainWindow::setSysTabLabels(int LabelID, int rowNum, char StatString[], char StatVal[])
{
    switch(LabelID)
    {
        case 1:
        {
            sysStatusStat1 = new QLabel(sysStatusLowerW);
            sysStatusVal1 = new QLabel(sysStatusLowerW);
            sysStatusStat1->setText(StatString);
            sysStatusVal1->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat1,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal1,rowNum,1);
            break;
        }
        case 2:
        {
            sysStatusStat2 = new QLabel(sysStatusLowerW);
            sysStatusVal2 = new QLabel(sysStatusLowerW);
            sysStatusStat2->setText(StatString);
            sysStatusVal2->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat2,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal2,rowNum,1);
            break;
        }
        case 3:
        {
            sysStatusStat3 = new QLabel(sysStatusLowerW);
            sysStatusVal3 = new QLabel(sysStatusLowerW);
            sysStatusStat3->setText(StatString);
            sysStatusVal3->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat3,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal3,rowNum,1);
            break;
        }
        case 4:
        {
            sysStatusStat4 = new QLabel(sysStatusLowerW);
            sysStatusVal4 = new QLabel(sysStatusLowerW);
            sysStatusStat4->setText(StatString);
            sysStatusVal4->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat4,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal4,rowNum,1);
            break;
        }
        case 5:
        {
            sysStatusStat5 = new QLabel(sysStatusLowerW);
            sysStatusVal5 = new QLabel(sysStatusLowerW);
            sysStatusStat5->setText(StatString);
            sysStatusVal5->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat5,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal5,rowNum,1);
            break;
        }
        case 6:
        {
            sysStatusStat6 = new QLabel(sysStatusLowerW);
            sysStatusVal6 = new QLabel(sysStatusLowerW);
            sysStatusStat6->setText(StatString);
            sysStatusVal6->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat6,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal6,rowNum,1);
            break;
        }
        case 7:
        {
            sysStatusStat7 = new QLabel(sysStatusLowerW);
            sysStatusVal7 = new QLabel(sysStatusLowerW);
            sysStatusStat7->setText(StatString);
            sysStatusVal7->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat7,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal7,rowNum,1);
            break;
        }
        case 8:
        {
            sysStatusStat8 = new QLabel(sysStatusLowerW);
            sysStatusVal8 = new QLabel(sysStatusLowerW);
            sysStatusStat8->setText(StatString);
            sysStatusVal8->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat8,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal8,rowNum,1);
            break;
        }
        case 9:
        {
            sysStatusStat9 = new QLabel(sysStatusLowerW);
            sysStatusVal9 = new QLabel(sysStatusLowerW);
            sysStatusStat9->setText(StatString);
            sysStatusVal9->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat9,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal9,rowNum,1);
            break;
        }
        case 10:
        {
            sysStatusStat10 = new QLabel(sysStatusLowerW);
            sysStatusVal10 = new QLabel(sysStatusLowerW);
            sysStatusStat10->setText(StatString);
            sysStatusVal10->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat10,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal10,rowNum,1);
            break;
        }
        case 11:
        {
            sysStatusStat11 = new QLabel(sysStatusLowerW);
            sysStatusVal11 = new QLabel(sysStatusLowerW);
            sysStatusStat11->setText(StatString);
            sysStatusVal11->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat11,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal11,rowNum,1);
            break;
        }
        case 12:
        {
            sysStatusStat12 = new QLabel(sysStatusLowerW);
            sysStatusVal12 = new QLabel(sysStatusLowerW);
            sysStatusStat12->setText(StatString);
            sysStatusVal12->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat12,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal12,rowNum,1);
            break;
        }
        case 13:
        {
            sysStatusStat13 = new QLabel(sysStatusLowerW);
            sysStatusVal13 = new QLabel(sysStatusLowerW);
            sysStatusStat13->setText(StatString);
            sysStatusVal13->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat13,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal13,rowNum,1);
            break;
        }
        case 14:
        {
            sysStatusStat14 = new QLabel(sysStatusLowerW);
            sysStatusVal14 = new QLabel(sysStatusLowerW);
            sysStatusStat14->setText(StatString);
            sysStatusVal14->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat14,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal14,rowNum,1);
            break;
        }
        case 15:
        {
            sysStatusStat15 = new QLabel(sysStatusLowerW);
            sysStatusVal15 = new QLabel(sysStatusLowerW);
            sysStatusStat15->setText(StatString);
            sysStatusVal15->setText(StatVal);
            sysStatusGridLayout->addWidget(sysStatusStat15,rowNum,0);
            sysStatusGridLayout->addWidget(sysStatusVal15,rowNum,1);
            break;
        }
        default:break;
    }
}

//Change the text of system status val labels
void MainWindow::setSysStatusValText(int lblID,char LabelString[])
{
    switch(lblID)
    {
        case 1: sysStatusVal1->setText(LabelString);break;
        case 2: sysStatusVal2->setText(LabelString);break;
        case 3: sysStatusVal3->setText(LabelString);break;
        case 4: sysStatusVal4->setText(LabelString);break;
        case 5: sysStatusVal5->setText(LabelString);break;
        case 6: sysStatusVal6->setText(LabelString);break;
        case 7: sysStatusVal7->setText(LabelString);break;
        case 8: sysStatusVal8->setText(LabelString);break;
        case 9: sysStatusVal9->setText(LabelString);break;
        case 10: sysStatusVal10->setText(LabelString);break;
        case 11: sysStatusVal11->setText(LabelString);break;
        case 12: sysStatusVal12->setText(LabelString);break;
        case 13: sysStatusVal13->setText(LabelString);break;
        case 14: sysStatusVal14->setText(LabelString);break;
        case 15: sysStatusVal15->setText(LabelString);break;
        default: break;
    }
}

//****************************************************//
//***********System Diagram Functions*****************//
//****************************************************//

void MainWindow::refitScene()
{
    sysDiagramDraw->setSceneRect(0,0,sysDiagramDraw->frameSize().width(),sysDiagramDraw->frameSize().height());
}

//Creates pens and brushes
void MainWindow::setupSysPensandBrushes()
{
    greenBrush = new QBrush(Qt::green);
    redBrush = new QBrush(Qt::red);
    blueBrush = new QBrush(Qt::blue);
    yellowBrush = new QBrush(Qt::yellow);
    blackPen = new QPen(Qt::black);
    greenPen = new QPen(Qt::green);
    redPen = new QPen(Qt::red);
    blackPen->setWidth(1);
    greenPen->setWidth(4);
    redPen->setWidth(4);
}

//Creates rectangle objects and places them in the scene
void MainWindow::setSysDiagramRect(int RectID, int x, int y, int w, int h, QPen pen, QBrush brush)
{
    switch(RectID)
    {
    case 1:
    {
        sysDiagramRect1 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 2:
    {
        sysDiagramRect2 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 3:
    {
        sysDiagramRect3 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 4:
    {
        sysDiagramRect4 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 5:
    {
        sysDiagramRect5 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 6:
    {
        sysDiagramRect6 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 7:
    {
        sysDiagramRect7 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 8:
    {
        sysDiagramRect8 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 9:
    {
        sysDiagramRect9 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 10:
    {
        sysDiagramRect10 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }
    case 11:
    {
        sysDiagramRect11 = sysDiagramScene->addRect(x,y,w,h,pen,brush);
        break;
    }

    default: break;
    }
}

//Changes the color of the rectangle items in the system diagram
void MainWindow::changeSysDiagramRect(int RectID, int BrushID)
{
    switch(RectID)
    {
        case 1:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect1->setBrush(*greenBrush);break;
                case 2:sysDiagramRect1->setBrush(*redBrush);break;
                case 3:sysDiagramRect1->setBrush(*blueBrush);break;
                case 4:sysDiagramRect1->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 2:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect2->setBrush(*greenBrush);break;
                case 2:sysDiagramRect2->setBrush(*redBrush);break;
                case 3:sysDiagramRect2->setBrush(*blueBrush);break;
                case 4:sysDiagramRect2->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 3:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect3->setBrush(*greenBrush);break;
                case 2:sysDiagramRect3->setBrush(*redBrush);break;
                case 3:sysDiagramRect3->setBrush(*blueBrush);break;
                case 4:sysDiagramRect3->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 4:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect4->setBrush(*greenBrush);break;
                case 2:sysDiagramRect4->setBrush(*redBrush);break;
                case 3:sysDiagramRect4->setBrush(*blueBrush);break;
                case 4:sysDiagramRect4->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 5:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect5->setBrush(*greenBrush);break;
                case 2:sysDiagramRect5->setBrush(*redBrush);break;
                case 3:sysDiagramRect5->setBrush(*blueBrush);break;
                case 4:sysDiagramRect5->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 6:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect6->setBrush(*greenBrush);break;
                case 2:sysDiagramRect6->setBrush(*redBrush);break;
                case 3:sysDiagramRect6->setBrush(*blueBrush);break;
                case 4:sysDiagramRect6->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 7:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect7->setBrush(*greenBrush);break;
                case 2:sysDiagramRect7->setBrush(*redBrush);break;
                case 3:sysDiagramRect7->setBrush(*blueBrush);break;
                case 4:sysDiagramRect7->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 8:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect8->setBrush(*greenBrush);break;
                case 2:sysDiagramRect8->setBrush(*redBrush);break;
                case 3:sysDiagramRect8->setBrush(*blueBrush);break;
                case 4:sysDiagramRect8->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 9:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect9->setBrush(*greenBrush);break;
                case 2:sysDiagramRect9->setBrush(*redBrush);break;
                case 3:sysDiagramRect9->setBrush(*blueBrush);break;
                case 4:sysDiagramRect9->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 10:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect10->setBrush(*greenBrush);break;
                case 2:sysDiagramRect10->setBrush(*redBrush);break;
                case 3:sysDiagramRect10->setBrush(*blueBrush);break;
                case 4:sysDiagramRect10->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        case 11:
        {
            switch(BrushID)
            {
                case 1:sysDiagramRect11->setBrush(*greenBrush);break;
                case 2:sysDiagramRect11->setBrush(*redBrush);break;
                case 3:sysDiagramRect11->setBrush(*blueBrush);break;
                case 4:sysDiagramRect11->setBrush(*yellowBrush);break;
                default:break;
            }
            break;
        }
        default: break;
    }

}

//Changes the brush of a rectangle item to a gradient
void MainWindow::setSysDiagramRectGradient(int RectID, char RGB1[], char RGB2[])
{
    switch(RectID)
    {
        case 1:
        {
            QRectF Rectangle = sysDiagramRect1->rect();
            sysDiagramRect1Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect1Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect1Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect1->setBrush(*sysDiagramRect1Gradient);
            break;
        }
        case 2:
        {
            QRectF Rectangle = sysDiagramRect2->rect();
            sysDiagramRect2Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect2Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect2Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect2->setBrush(*sysDiagramRect2Gradient);
            break;
        }
        case 3:
        {
            QRectF Rectangle = sysDiagramRect3->rect();
            sysDiagramRect3Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect3Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect3Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect3->setBrush(*sysDiagramRect3Gradient);
            break;
        }
        case 4:
        {
            QRectF Rectangle = sysDiagramRect4->rect();
            sysDiagramRect4Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect4Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect4Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect4->setBrush(*sysDiagramRect4Gradient);
            break;
        }
        case 5:
        {
            QRectF Rectangle = sysDiagramRect5->rect();
            sysDiagramRect5Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect5Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect5Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect5->setBrush(*sysDiagramRect5Gradient);
            break;
        }
        case 6:
        {
            QRectF Rectangle = sysDiagramRect6->rect();
            sysDiagramRect6Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect6Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect6Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);
            break;
        }
        case 7:
        {
            QRectF Rectangle = sysDiagramRect7->rect();
            sysDiagramRect7Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect7Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect7Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect7->setBrush(*sysDiagramRect7Gradient);
            break;
        }
        case 8:
        {
            QRectF Rectangle = sysDiagramRect8->rect();
            sysDiagramRect8Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
            sysDiagramRect8Gradient->setColorAt(0.0,RGB1);
            sysDiagramRect8Gradient->setColorAt(1.0,RGB2);
            sysDiagramRect8->setBrush(*sysDiagramRect8Gradient);
            break;
        }
    case 9:
    {
        QRectF Rectangle = sysDiagramRect9->rect();
        sysDiagramRect9Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
        sysDiagramRect9Gradient->setColorAt(0.0,RGB1);
        sysDiagramRect9Gradient->setColorAt(1.0,RGB2);
        sysDiagramRect9->setBrush(*sysDiagramRect9Gradient);
        break;
    }
    case 10:
    {
        QRectF Rectangle = sysDiagramRect10->rect();
        sysDiagramRect10Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
        sysDiagramRect10Gradient->setColorAt(0.0,RGB1);
        sysDiagramRect10Gradient->setColorAt(1.0,RGB2);
        sysDiagramRect10->setBrush(*sysDiagramRect10Gradient);
        break;
    }
    case 11:
    {
        QRectF Rectangle = sysDiagramRect11->rect();
        sysDiagramRect11Gradient = new QLinearGradient(Rectangle.x(),Rectangle.y(),Rectangle.x()+Rectangle.width(),Rectangle.y()+Rectangle.height());
        sysDiagramRect11Gradient->setColorAt(0.0,RGB1);
        sysDiagramRect11Gradient->setColorAt(1.0,RGB2);
        sysDiagramRect11->setBrush(*sysDiagramRect11Gradient);
        break;
    }
        default: break;
    }

}

//Creates ellipse objects and places them in the scene
void MainWindow::setSysDiagramEli(int ElipseID, int x, int y, int w, int h, QPen pen, QBrush brush)
{
    switch(ElipseID)
    {
        case 1:
        {
            sysDiagramEllipse1 = sysDiagramScene->addEllipse(x,y,w,h,pen,brush);
            break;
        }
        default: break;
    }
}

//Changes the color of the ellipse items in the system diagram
void MainWindow::changeSysDiagramEli(int ElipseID, int BrushID)
{
    switch(ElipseID)
    {
        case 1:
        {
            switch(BrushID)
            {
            case 1:sysDiagramEllipse1->setBrush(*greenBrush);break;
            case 2:sysDiagramEllipse1->setBrush(*redBrush);break;
            case 3:sysDiagramEllipse1->setBrush(*blueBrush);break;
            case 4:sysDiagramEllipse1->setBrush(*yellowBrush);break;
            default:break;
            }

            break;
        }
        default: break;
    }
}

void MainWindow::setSysDiagramEliGradient(int ElipseID, char RGB1[], char RGB2[])
{
    switch(ElipseID)
    {
        case 1:
        {
            QRectF Rectangle = sysDiagramEllipse1->rect();

            sysDiagramEllipse1Gradient = new QRadialGradient(Rectangle.x()+Rectangle.width()/2,Rectangle.y()+Rectangle.height()/2,Rectangle.width()/2,Rectangle.x()+Rectangle.width()/2,Rectangle.y()+Rectangle.height()/2);
            sysDiagramEllipse1Gradient->setColorAt(0.0,RGB1);
            sysDiagramEllipse1Gradient->setColorAt(1.0,RGB2);
            sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);
            break;
        }
        default: break;
    }

}

//Creates Line objects and places them in the scene
void MainWindow::setSysDiagramLine(int LineID, int x1, int y1, int x2, int y2, QPen pen)
{
    switch(LineID)
    {
        case 1:
        {
            sysDiagramLine1 = sysDiagramScene->addLine(x1,y1,x2,y2,pen);
            break;
        }
        default: break;
    }
}

//Creates Line objects and places them in the scene
void MainWindow::changeSysDiagramLine(int LineID, int x1, int y1, int x2, int y2, int PenID)
{
    switch(LineID)
    {
        case 1:
        {
            switch(PenID)
            {
                case 1: sysDiagramLine1->setPen(*blackPen); break;
                case 2: sysDiagramLine1->setPen(*greenPen); break;
                case 3: sysDiagramLine1->setPen(*redPen); break;
                default: break;
            }
            sysDiagramLine1->setLine(x1,y1,x2,y2);

        }
        default: break;
    }
}

//****************************************************//
//**************Menu Action Functions*****************//
//****************************************************//

//Action taken when "Close" is selected from menu
//  shutdown Embedded system, close COM port, close application
void MainWindow::on_actionClose_triggered()
{
    //Send shutdown message to MSP430

    //Shutdown COM port

    //Close application
    close();
}

//Action taken when "Settings" is selected from menu
//  Open settings window
void MainWindow::on_actionSettings_triggered()
{
    settings = new Dialog(this);
    settings->exec();
    //settings->show();
    //settings->setModal(true);
    /*Dialog settings;
    settings.setModal(true);
    settings.setWindowTitle("Settings");
    settings.show();
    settings.exec();*/
    //emit showSettings();
}

//Action taken when "Detect_System" is selected from menu
//  Send signal over COM to system requesting system ID
void MainWindow::on_actionDetect_System_triggered()
{

}

void MainWindow::resizeEvent (QResizeEvent * event )
{
    sysDiagramSceneBounds = sysDiagramScene->itemsBoundingRect();
    sysDiagramSceneBounds.setWidth(sysDiagramSceneBounds.width()*1.0);
    sysDiagramSceneBounds.setHeight(sysDiagramSceneBounds.height()*1.0);
    sysDiagramDraw->fitInView(sysDiagramSceneBounds, Qt::KeepAspectRatio);
    QMainWindow::resizeEvent(event);
}

//********************************************************//
//**************Data Processing Functions*****************//
//********************************************************//

//Message Passed to MainWindow after being CRC checked.
//No longer includes CRC
void MainWindow::UART_RX_Message(char RX_MSG[])
{

}
