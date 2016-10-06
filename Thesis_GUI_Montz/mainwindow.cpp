#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <math.h>
#include <QFileDialog>
#include "colorkey.h"

//MainWindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //processTimer = new QTimer(this);
    //transmitTimer = new QTimer(this);
    //offsetTimer = new QTimer(this);
    rectExists = false;
    imgLoaded = false;
    elapsedTime = new QElapsedTimer;
    elapsedTime->start();

    simulationTimer = new QTimer(this);
    simulationTimer->setTimerType(Qt::PreciseTimer);

    //simulationTimer->setTimerType(Qt::TimerType);
    simulationTimer->setSingleShot(true);
    simulationTimer->setInterval(100);
    connect(simulationTimer,SIGNAL(timeout()),this,SLOT(simulationTimer_triggered()));

    //offsetTimer->setSingleShot(true);
    //processTimer->setSingleShot(false);
    //transmitTimer->setSingleShot(false);
    myImgReader = new ImgdatReader(this);
    myImgReader->setVisible(false);
    connect(this,SIGNAL(saveCsvFile(QString)),myImgReader,SLOT(saveCsvFile(QString)));
    InitializeMainWindow();
    InitializeCentralWidget();
    InitializeStatusBar();
    InitializeCommandsWidget();
    setupSysPensandBrushes();

    //Create MyUART object using crc16 ccittXModem
    myUART = new MyUART(MyUART::crc16ccittXModem);

    //Connect rx signals to rx GUI light and tx signals to tx GUI light
    connect(myUART,SIGNAL(rxSignal()),this,SLOT(setRXBlink()));
    connect(myUART,SIGNAL(txSignal()),this,SLOT(setTXBlink()));

    //Connect MainWindow to MyUART
    connect(this,SIGNAL(sendDetectSystemSignal(bool)),myUART,SLOT(sendDetectSystem(bool)));
    connect(myUART,SIGNAL(statusSignal(int,int)),this,SLOT(statusSlot(int,int)));
    connect(this,SIGNAL(sendAbortShutdownSignal()),myUART,SLOT(sendAbortShutdown()));
    connect(myUART,SIGNAL(errorShutdownSignal(int)),this,SLOT(errorShutdownSlot(int)));
    connect(this,SIGNAL(sendAckSignal()),myUART,SLOT(sendACK()));
    connect(myUART,SIGNAL(ackSignal(int)),this,SLOT(ackSlot(int)));
    connect(this,SIGNAL(sendBeginProcessSignal()),myUART,SLOT(sendBeginProcess()));
    connect(this,SIGNAL(sendBeginTransmittingDataSignal()),myUART,SLOT(sendBeginTransmittingData()));
    connect(this,SIGNAL(sendOrientationData(double,double,double)),myUART,SLOT(sendOrientationData(double,double,double)));
    connect(myUART,SIGNAL(reqOrientationDataSignal(int)),this,SLOT(reqOrientationDataSlot(int)));
    connect(myUART,SIGNAL(DataTransferSignal(int,QByteArray)),this,SLOT(dataTransferSignal(int,QByteArray)));

    orientationIndex = 0;

    gtzIntValidator = new QIntValidator(this);
    gtzIntValidator->setBottom(1);

    numCyclesLineEdit->setValidator(gtzIntValidator);
    timeToReachTxLineEdit->setValidator(gtzIntValidator);
    orbitalPeriodLineEdit->setValidator(gtzIntValidator);

    //connect(offsetTimer,SIGNAL(timeout()),this,SLOT(offsetTimer_triggered()));
    //connect(processTimer,SIGNAL(timeout()),this,SLOT(processTimer_triggered()));
    //connect(transmitTimer,SIGNAL(timeout()),this,SLOT(transmitTimer_triggered()));

    connect(logsListListView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickedOnLogFile(QModelIndex)));

    connect(imgListListView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickedOnImgFile(QModelIndex)));


    //SetSysTab(1);
    //changeSysDiagramRect(1,4);
    //changeSysDiagramEli(1,4);
    //changeSysDiagramLine(1, 212, 31, 244, 31, 2);
    //changeSysDiagramLine(1, 212, 30, 250, 15, 3);
    //setSysDiagramRectGradient(1, "#FF0000", "#760000");
    //setSysDiagramRectGradient(1, "#8E0E00", "1F1C18");

    //clearSystemTab();
    setStatusBarText("Verify settings and connect to system.");
    setColorScheme();
}

//MainWindow destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete myUART;
    delete settings;
    delete myImgReader;

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
    setMinimumWidth(1260);//1100);
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
    imgSplitter->setStyleSheet("background-color: #000000");
    imgSplitter->setHandleWidth(5);
    imgSplitter->setChildrenCollapsible(false);

    //Splitter for Logs tab
    logsSplitter = new QSplitter(this);
    logsSplitter->setStyleSheet("background-color: #000000");
    logsSplitter->setHandleWidth(5);
    logsSplitter->setChildrenCollapsible(false);

    //Borders for tabs
    sysTabBorder = new QWidget(this);
    sysTabBorderLayout = new QVBoxLayout;
    sysTabBorder->setLayout(sysTabBorderLayout);
    sysTabBorderLayout->addWidget(sysSplitter);
    sysTabBorder->setStyleSheet("background-color: #F5F5F5");
    imgTabBorder = new QWidget(this);
    imgTabBorderLayout = new QVBoxLayout;
    imgTabBorder->setLayout(imgTabBorderLayout);
    imgTabBorderLayout->addWidget(imgSplitter);
    imgTabBorder->setStyleSheet("background-color: #F5F5F5");
    logsTabBorder = new QWidget(this);
    logsTabBorderLayout = new QVBoxLayout;
    logsTabBorder->setLayout(logsTabBorderLayout);
    logsTabBorderLayout->addWidget(logsSplitter);
    logsTabBorder->setStyleSheet("background-color: #F5F5F5");

    //Add Splitters as tabs
    cwTabWidget->addTab(sysTabBorder,tr("System"));
    cwTabWidget->addTab(imgTabBorder,tr("Images"));
    cwTabWidget->addTab(logsTabBorder,tr("Logs"));

    //Left collumn of system tab splitter (System Status)
    sysStatusW = new QWidget(this);
    sysStatusW->setMaximumWidth(320);
    sysStatusW->setMinimumWidth(320);
    sysStatusVLayout = new QVBoxLayout;
    sysStatusLbl = new QLabel(this);
    sysStatusLbl->setMinimumHeight(20);
    sysStatusLbl->setMaximumHeight(20);
    sysStatusLbl->setText("System Status");
    sysStatusLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysStatusLowerW = new QWidget(this);
    sysStatusLowerW->setStyleSheet("QWidget{background-color: #F0F0F0;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    sysStatusGridLayout = new QGridLayout;
    sysStatusLowerW->setLayout(sysStatusGridLayout);
    sysStatusLowerW->setMinimumWidth(200);
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
    sysDiagramLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysDiagramDraw = new QGraphicsView(this);
    sysDiagramDraw->setStyleSheet("background-color: #F0F0F0");
    sysDiagramScene = new QGraphicsScene(this);
    sysDiagramDraw->setScene(sysDiagramScene);
    sysDiagramVLayout->addWidget(sysDiagramLbl);
    sysDiagramVLayout->addWidget(sysDiagramDraw);
    sysDiagramVLayout->setContentsMargins(0,2,0,2);
    sysDiagramW->setLayout(sysDiagramVLayout);
    sysSplitter->addWidget(sysDiagramW);
    sysDiagramEllipse1Text = new QGraphicsTextItem;
    sysDiagramEllipse1Text->setHtml("<font size=\"48\"><b>B.B.</b></font>");//setPlainText("A");
    sysDiagramEllipse1Text->setPos(335,102);
    sysDiagramEllipse1Text->setZValue(2);

    //sysDiagramScene->addItem(sysDiagramEllipse1Text);

    //sysDiagramDraw->setSceneRect(0,0);

    //Right collumn of system tab splitter (commands)
    sysCommandsW = new QWidget(this);
    sysCommandsW->setMinimumWidth(280);
    sysCommandsW->setMaximumWidth(280);
    sysCommandsVLayout = new QVBoxLayout;
    sysCommandsLbl = new QLabel(this);
    sysCommandsLbl->setMinimumHeight(20);
    sysCommandsLbl->setMaximumHeight(20);
    sysCommandsLbl->setText("Commands");
    sysCommandsLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysCommandsSubWidget = new QWidget(this);
    sysCommandsSubWidget->setStyleSheet("background-color: #F0F0F0");
    sysCommandsVLayout->addWidget(sysCommandsLbl);
    sysCommandsVLayout->addWidget(sysCommandsSubWidget);
    sysCommandsVLayout->setContentsMargins(0,2,2,2);
    sysCommandsW->setLayout(sysCommandsVLayout);
    sysSplitter->addWidget(sysCommandsW);
    cwTabWidget->setStyleSheet("QTabBar::tab {min-width: 20ex;font-size: 16px;}");

    sysSimulationLbl = new QLabel(this);
    sysSimulationLbl->setMinimumHeight(20);
    sysSimulationLbl->setMaximumHeight(20);
    sysSimulationLbl->setText("Simulation Visualization");
    sysSimulationLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    sysSimulationWidget = new QWidget(this);
    sysSimulationWidget->setStyleSheet("background-color: #F0F0F0");
    sysSimulationLayout = new QVBoxLayout;
    orbitAnimation = new OrbitalAnimationWidget(this);
    orbitAnimation->resetWidget();
    sysSimulationFiller = new QWidget(this);
    sysSimulationLayout->addWidget(orbitAnimation,0,Qt::AlignCenter);
    sysSimulationLayout->addWidget(sysSimulationFiller);
    sysSimulationWidget->setLayout(sysSimulationLayout);
    sysCommandsVLayout->addWidget(sysSimulationLbl);
    sysCommandsVLayout->addWidget(sysSimulationWidget);

    //Image tab
    //*********
    //Image left collumn
    imgListLeftWidget = new QWidget(this);
    imgListLeftWidget->setMaximumWidth(230);
    imgListLeftWidget->setMinimumWidth(230);
    imgListLeftLayout = new QVBoxLayout;
    imgListLabel = new QLabel(this);
    imgListLabel->setMinimumHeight(20);
    imgListLabel->setMaximumHeight(20);
    imgListLabel->setText("Image List");
    imgListLabel->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    imgListW = new QWidget(this);
    imgListW->setStyleSheet("QWidget{background-color: #F0F0F0;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    imgListLayout = new QVBoxLayout;
    imgListListView = new QListView(this);
    imgListLayout->addWidget(imgListListView);
    imgListW->setLayout(imgListLayout);
    imgListW->setMinimumWidth(200);
    imgListLeftLayout->addWidget(imgListLabel);
    imgListLeftLayout->addWidget(imgListW);
    imgListLeftLayout->setContentsMargins(2,2,0,2);
    imgListLeftWidget->setLayout(imgListLeftLayout);
    imgSplitter->addWidget(imgListLeftWidget);

    imgfDir = new QString;
    imgfDirOld = new QString;
    QSettings imgtmpSett("MontzThesis","GUISettingsFile");
    imgtmpSett.beginGroup("Dialog");
    QString imgsPath = imgtmpSett.value("Image Save Dir", "C:/").toString() + "/";
    imgtmpSett.endGroup();
    imgFileModel = new QFileSystemModel(this);
    imgFileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList imgfilters;
    imgfilters << "*.imgdata";
    imgFileModel->setNameFilters(imgfilters);
    imgFileModel->setNameFilterDisables(false);
    imgListListView->setModel(imgFileModel);
    imgListListView->setRootIndex(imgFileModel->setRootPath(imgsPath));

    //Image central collumn
    imgDisplayCentralWidget = new QWidget(this);
    imgDisplayCentralWidget->setMinimumWidth(420);
    imgDisplayCentralLayout = new QVBoxLayout;
    imgDisplayLabel = new QLabel(this);
    imgDisplayLabel->setMinimumHeight(20);
    imgDisplayLabel->setMaximumHeight(20);
    imgDisplayLabel->setText("Image Display");
    imgDisplayLabel->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    imgDisplayW = new QWidget(this);
    //imgDisplayW->setStyleSheet("QWidget{background-color: #FFFFFF;}QLabel{background-color: #FFFFFF; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    imgDisplayW->setStyleSheet("QWidget{background-color: #7F7F7F;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");

    imgDisplayLayout = new QVBoxLayout;
    imgDisplayView = new QGraphicsView(this);
    imgDisplayView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    imgDisplayScene = new myCustomScene(this);//QGraphicsScene(this);
    imgDisplayPointerRect = new QGraphicsRectItem;
    imgHistogramLine = new QGraphicsLineItem;
    imgColorbarLine = new QGraphicsLineItem;
    connect(myImgReader,SIGNAL(scenePressed(int,QPointF,int)),this,SLOT(scenePressed_endSlot(int,QPointF,int)));
    imgDisplayView->setScene(imgDisplayScene);

    imgDisplayLayout->addWidget(imgDisplayView);
    imgDisplayW->setLayout(imgDisplayLayout);
    imgOptionsLabel = new QLabel(this);
    imgOptionsLabel->setMinimumHeight(20);
    imgOptionsLabel->setMaximumHeight(20);
    imgOptionsLabel->setText("Image Options");
    imgOptionsLabel->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    imgOptionsW = new QWidget(this);
    imgOptionsW->setStyleSheet("QWidget{background-color: #F0F0F0;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignRight;}");
    //imgOptionsLayout = new QHBoxLayout;
    imgOptionsLayout = new QGridLayout;
    imgOpZoomIn = new QPushButton("Zoom In",this);
    imgOpZoomOut = new QPushButton("Zoom out",this);
    imgOpZoomReset = new QPushButton("Reset Zoom",this);
    imgOpColorscaleReset = new QPushButton("Reset Color Scale",this);
    zoomCount = 0;
    imgOpColormapLabel = new QLabel("Colormap:",this);
    imgOpInvertCheckBox = new QCheckBox("Invert Colormap",this);
    imgMinScaler = new QSlider(Qt::Horizontal);
    imgMinScaler->setMinimum(0);
    imgMinScaler->setMaximum(255);
    imgMinScaler->setValue(0);
    imgMinScaler->setEnabled(false);
    imgMinScaler->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    imgMaxScaler = new QSlider(Qt::Horizontal);
    imgMaxScaler->setMinimum(0);
    imgMaxScaler->setMaximum(255);
    imgMaxScaler->setValue(255);
    imgMaxScaler->setEnabled(false);
    imgMinScalerLabel = new QLabel("Low End:",this);
    imgMaxScalerLabel = new QLabel("High End:",this);
    imgSaveButton = new QPushButton("Save",this);
    colorbar = new QGraphicsPixmapItem;
    colorbar->setEnabled(false);
    connect(imgOpInvertCheckBox,SIGNAL(pressed()),myImgReader,SLOT(colormapInverterChanged()));
    connect(imgOpInvertCheckBox,SIGNAL(released()),this,SLOT(InvertingCheckbox_released()));

    connect(imgMinScaler,SIGNAL(sliderMoved(int)),myImgReader,SLOT(minImgScaleChanged(int)));
    //connect(imgMinScaler,SIGNAL(sliderReleased()),this,SLOT(InvertingCheckbox_released()));
    connect(imgMinScaler,SIGNAL(sliderMoved(int)),this,SLOT(minSliderMoved(int)));

    connect(imgMaxScaler,SIGNAL(sliderMoved(int)),myImgReader,SLOT(maxImgScaleChanged(int)));
    connect(imgMaxScaler,SIGNAL(sliderMoved(int)),this,SLOT(maxSliderMoved(int)));
    //connect(imgMaxScaler,SIGNAL(sliderReleased()),this,SLOT(InvertingCheckbox_released()));
    connect(myImgReader,SIGNAL(updateImg()),this,SLOT(updateImage()));

    imgOpColormapCombo = new QComboBox(this);
    //imgOpZoomIn->setStyleSheet("QPushButton {background-color: lightgray;} QPushButton:hover {background-color:");
    imgOpZoomIn->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c; border-style: outset; border-width: 2px;}");
    //imgOpZoomOut->setStyleSheet("background-color: lightgray");
    imgOpZoomOut->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c;  border-style: outset; border-width: 2px;}");
    //imgOpZoomReset->setStyleSheet("background-color: lightgray");
    imgOpZoomReset->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c;  border-style: outset; border-width: 2px;}");
    imgOpColorscaleReset->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c;  border-style: outset; border-width: 2px;}");
    imgSaveButton->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c;  border-style: outset; border-width: 2px;}");
    //imgOpColormapCombo->setStyleSheet("background-color: lightgray");
    //imgOpColormapCombo->setStyleSheet("QComboBox {background-color: lightgrey; font: bold 14px;} QComboBox:hover {background-color:#9c9c9c;  border-style: outset; border-width: 2px;}");
    imgOpColormapCombo->addItem("Thermal");
    imgOpColormapCombo->addItem("Fire");
    imgOpColormapCombo->addItem("Dawn");
    imgOpColormapCombo->addItem("RedBlue");
    imgOpColormapCombo->addItem("Dusk");
    imgOpColormapCombo->addItem("Ice");
    imgOpColormapCombo->addItem("Kryptonite");
    imgOpColormapCombo->addItem("Seashore");
    imgOpColormapCombo->addItem("Gray");
    imgOpColormapCombo->addItem("Reds");
    imgOpColormapCombo->addItem("Golds");
    imgOpColormapCombo->addItem("Green");
    imgOpColormapCombo->addItem("Teals");
    imgOpColormapCombo->addItem("Blues");
    imgOpColormapCombo->addItem("Purples");

    connect(imgOpColormapCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(colormapCombo_changed(int)));

//    imgOptionsLayout->addWidget(imgOpZoomIn);
//    imgOptionsLayout->addWidget(imgOpZoomOut);
//    imgOptionsLayout->addWidget(imgOpZoomReset);
//    imgOptionsLayout->addWidget(imgOpColormapLabel);
//    imgOptionsLayout->addWidget(imgOpColormapCombo);
//    imgOptionsLayout->addWidget(imgOpInvertCheckBox);
//    imgOptionsLayout->addWidget(imgMinScaler);
//    imgOptionsLayout->addWidget(imgMaxScaler);
    imgOptionsLayout->addWidget(imgOpZoomIn,0,0,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpZoomOut,0,1,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpZoomReset,0,2,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpColormapLabel,0,3,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpColormapCombo,0,4,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpInvertCheckBox,0,5,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgMinScalerLabel,1,0,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgMinScaler,1,1,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgMaxScalerLabel,1,2,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgMaxScaler,1,3,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgOpColorscaleReset,1,4,1,1,Qt::AlignCenter);
    imgOptionsLayout->addWidget(imgSaveButton,1,5,1,1,Qt::AlignCenter);

    imgOptionsW->setLayout(imgOptionsLayout);
    imgDisplayCentralLayout->addWidget(imgDisplayLabel);
    imgDisplayCentralLayout->addWidget(imgDisplayW);
    imgDisplayCentralLayout->addWidget(imgOptionsLabel);
    imgDisplayCentralLayout->addWidget(imgOptionsW);
    imgDisplayCentralLayout->setContentsMargins(0,2,0,2);
    imgDisplayCentralWidget->setLayout(imgDisplayCentralLayout);
    imgSplitter->addWidget(imgDisplayCentralWidget);

    //Img right collumn
    //Right collumn of system tab splitter (commands)
    imgStatsLeftWidget = new QWidget(this);
    imgStatsLeftWidget->setMinimumWidth(280);
    imgStatsLeftWidget->setMaximumWidth(280);
    imgStatsLeftLayout = new QVBoxLayout;
    imgStatsLabel = new QLabel(this);
    imgStatsLabel->setMinimumHeight(20);
    imgStatsLabel->setMaximumHeight(20);
    imgStatsLabel->setText("Image Statistics");
    imgStatsLabel->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    imgStatsW = new QWidget(this);
    imgStatsW->setStyleSheet("background-color: #F0F0F0");
    imgStatsLayout = new QVBoxLayout;



    imgStatsDateLabel = myImgReader->getDateLabel();
    imgStatsImageTypeLabel = myImgReader->getImageTypeLabel();
    imgStatsLatLabel = myImgReader->getLatLabel();
    imgStatsLonLabel = myImgReader->getLonLabel();
    imgStatsAziLabel = myImgReader->getAziLabel();
    imgStatsWidthLabel = myImgReader->getWidthLabel();
    imgStatsHeightLabel = myImgReader->getHeightLabel();
    imgStatsBytesPerPixelLabel = myImgReader->getBytesPerPixelLabel();
    imgStatsOrignialDataFormatLabel = myImgReader->getOriginalDataFormatLabel();
    imgStatsCameraPartNumLabel = myImgReader->getCameraPartNumLabel();
    imgStatsCameraUsedLabel = myImgReader->getCameraUsedLabel();
    imgStatsLensUsedLabel = myImgReader->getLensUsedLabel();
    imgStatsFovLabel = myImgReader->getFovLabel();
    imgStatsMinLabel = myImgReader->getMinValLabel();
    imgStatsMaxLabel = myImgReader->getMaxValLabel();
    imgStatsAvgLabel = myImgReader->getAvgValLabel();

    imgStatsHistoView = new QGraphicsView(this);
    //imgStatsHistoScene = new QGraphicsScene(this);
    imgStatsHistoScene = new myCustomScene(this);
    imgStatsHistoView->setScene(imgStatsHistoScene);
    //imgStatsHistoView->setBackgroundBrush(QBrush(QColor(Qt::green),Qt::SolidPattern));
    imgStatsHistoView->setMinimumHeight(200);
    //imgStatsHistoView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    imgStatsHistoView->setSceneRect(-0.5,19.5,256,171);



    minRectHistItem = new QGraphicsRectItem;
    maxRectHistItem = new QGraphicsRectItem;

    QLabel *spacerLabel = new QLabel(this);

    imgStatsFillerWidget = new QWidget(this);
    imgStatsLayout->addWidget(imgStatsDateLabel);
    imgStatsLayout->addWidget(imgStatsImageTypeLabel);
    imgStatsLayout->addWidget(imgStatsLatLabel);
    imgStatsLayout->addWidget(imgStatsLonLabel);
    imgStatsLayout->addWidget(imgStatsAziLabel);
    imgStatsLayout->addWidget(imgStatsWidthLabel);
    imgStatsLayout->addWidget(imgStatsHeightLabel);
    imgStatsLayout->addWidget(imgStatsBytesPerPixelLabel);
    imgStatsLayout->addWidget(imgStatsOrignialDataFormatLabel);
    imgStatsLayout->addWidget(imgStatsCameraPartNumLabel);
    imgStatsLayout->addWidget(imgStatsCameraUsedLabel);
    imgStatsLayout->addWidget(imgStatsLensUsedLabel);
    imgStatsLayout->addWidget(imgStatsFovLabel);
    imgStatsLayout->addWidget(imgStatsMinLabel);
    imgStatsLayout->addWidget(imgStatsMaxLabel);
    imgStatsLayout->addWidget(imgStatsAvgLabel);
    imgStatsLayout->addWidget(spacerLabel);
    imgStatsLayout->addWidget(imgStatsHistoView);
    imgStatsLayout->addWidget(imgStatsFillerWidget,1);



    imgStatsW->setLayout(imgStatsLayout);
    imgStatsLeftLayout->addWidget(imgStatsLabel);
    imgStatsLeftLayout->addWidget(imgStatsW);
    imgStatsLeftLayout->setContentsMargins(0,2,2,2);
    imgStatsLeftWidget->setLayout(imgStatsLeftLayout);
    imgSplitter->addWidget(imgStatsLeftWidget);
    cwTabWidget->setStyleSheet("QTabBar::tab {min-width: 20ex;font-size: 16px;}");

    connect(imgOpZoomIn,SIGNAL(released()),this,SLOT(zoomInButton_pressed()));
    connect(imgOpZoomOut,SIGNAL(released()),this,SLOT(zoomOutButton_pressed()));
    connect(imgOpZoomReset,SIGNAL(released()),this,SLOT(zoomResetButton_pressed()));
    connect(imgDisplayScene,SIGNAL(scenePosClicked(QPointF)),myImgReader,SLOT(SceneClicked(QPointF)));
    connect(imgOpColorscaleReset,SIGNAL(released()),this,SLOT(resetColormap()));
    connect(imgSaveButton,SIGNAL(released()),this,SLOT(saveImg()));


    imgOpColorscaleReset->setEnabled(false);
    //***********

    //Logs left collumn
    logsListW = new QWidget(this);
    logsListW->setMaximumWidth(230);
    logsListW->setMinimumWidth(230);
    logsListVLayout = new QVBoxLayout;
    logsListLbl = new QLabel(this);
    logsListLbl->setMinimumHeight(20);
    logsListLbl->setMaximumHeight(20);
    logsListLbl->setText("Log List");
    logsListLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    logsListLowerW = new QWidget(this);
    logsListLowerW->setStyleSheet("QWidget{background-color: #F0F0F0;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    logsGridLayout = new QVBoxLayout;
    logsListListView = new QListView(this);
    logsRefreshButton = new QPushButton(this);
    logsRefreshButton->setText("Refresh Open Log");
    logsRefreshButton->setStyleSheet("background-color: lightgray;");
    //logsListListView->setStyleSheet("Background-color: white; QScrollBar {background-color: red;}");
    connect(logsRefreshButton,SIGNAL(released()),this,SLOT(logRefreshButton_clicked()));


    logsGridLayout->addWidget(logsListListView);
    logsGridLayout->addWidget(logsRefreshButton);
    logsListLowerW->setLayout(logsGridLayout);
    logsListLowerW->setMinimumWidth(200);
    logsListVLayout->addWidget(logsListLbl);
    logsListVLayout->addWidget(logsListLowerW);
    logsListVLayout->setContentsMargins(2,2,0,2);
    logsListW->setLayout(logsListVLayout);
    logsSplitter->addWidget(logsListW);

    logsfDir = new QString;
    QSettings tmpSett("MontzThesis","GUISettingsFile");
    tmpSett.beginGroup("Dialog");
    QString sPath = tmpSett.value("Log Save Dir", "C:/").toString() + "/";
    tmpSett.endGroup();
    logsFileModel = new QFileSystemModel(this);
    logsFileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.comLog";
    logsFileModel->setNameFilters(filters);
    logsFileModel->setNameFilterDisables(false);
    logsListListView->setModel(logsFileModel);
    logsListListView->setRootIndex(logsFileModel->setRootPath(sPath));


    //Logs right collumn
    logsDisplayW = new QWidget(this);
    logsDisplayVLayout = new QVBoxLayout;
    logsDisplayLbl = new QLabel(this);
    logsDisplayLbl->setMinimumHeight(20);
    logsDisplayLbl->setMaximumHeight(20);
    logsDisplayLbl->setText("Log Display");
    logsDisplayLbl->setStyleSheet("background-color: #F0F0F0; font-size: 14px; padding: 20px; qproperty-alignment: AlignCenter;");
    logsDisplayLowerW = new QWidget(this);
    logsDisplayLowerW->setStyleSheet("QWidget{background-color: #F0F0F0;}QLabel{background-color: #F0F0F0; font-size: 14px; padding: 1px; qproperty-alignment: AlignLeft;}");
    logsDisplayLowerW->setMinimumWidth(200);
    logsDisplayLowerVLayout = new QVBoxLayout;
    logsDisplayTextBrowser = new QTextBrowser(this);
    logsDisplayLowerVLayout->addWidget(logsDisplayTextBrowser);
    logsDisplayTextBrowser->setStyleSheet("background-color: #002B36; font-size: 14px; color: #808F8F;");



    logsDisplayLowerW->setLayout(logsDisplayLowerVLayout);
    logsDisplayVLayout->addWidget(logsDisplayLbl);
    logsDisplayVLayout->addWidget(logsDisplayLowerW);
    logsDisplayVLayout->setContentsMargins(0,2,2,2);
    logsDisplayW->setLayout(logsDisplayVLayout);
    logsSplitter->addWidget(logsDisplayW);

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

void MainWindow::InitializeCommandsWidget()
{


    sysCommandsLayout = new QGridLayout;
    abortButton = new QPushButton("ABORT!");
    abortButton->setMinimumWidth(260);
    abortButton->setMinimumHeight(40);
    abortButton->setStyleSheet("QPushButton {background-color:rgb(255,00,00); font: bold 14px;} QPushButton:hover {background-color:rgb(200,00,00); font: bold 14px; border-style: outset; border-width: 2px; }");
    sysCommandsLayout->addWidget(abortButton,0,0,1,2,Qt::AlignCenter);


    beginProcessButton = new QPushButton("Begin Process");
    beginProcessButton->setMinimumWidth(260);
    beginProcessButton->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c; font: bold 14px; border-style: outset; border-width: 2px;}");
    sysCommandsLayout->addWidget(beginProcessButton,1,0,1,2,Qt::AlignCenter);


    beginTransmissionButton = new QPushButton("Begin Transmission");
    beginTransmissionButton->setMinimumWidth(260);
    beginTransmissionButton->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c; font: bold 14px; border-style: outset; border-width: 2px;}");
    sysCommandsLayout->addWidget(beginTransmissionButton,2,0,1,2,Qt::AlignCenter);

    numCyclesLabel = new QLabel("Number of Cycles:");
    numCyclesLabel->setStyleSheet("font-size: 14px");
    numCyclesLineEdit = new QLineEdit("1");
    numCyclesLineEdit->setAlignment(Qt::AlignRight);
    sysCommandsLayout->addWidget(numCyclesLabel,3,0,1,1,Qt::AlignLeft);
    sysCommandsLayout->addWidget(numCyclesLineEdit,3,1,1,1,Qt::AlignRight);

    timeToReachTxLabel = new QLabel("Time to reach TX Location(sec):");
    timeToReachTxLabel->setStyleSheet("font-size: 14px");
    timeToReachTxLineEdit = new QLineEdit("2700");
    timeToReachTxLineEdit->setAlignment(Qt::AlignRight);
    sysCommandsLayout->addWidget(timeToReachTxLabel,4,0,1,1,Qt::AlignLeft);
    sysCommandsLayout->addWidget(timeToReachTxLineEdit,4,1,1,1,Qt::AlignRight);

    orbitalPeriodLabel = new QLabel("Orbital Period(sec):");
    orbitalPeriodLabel->setStyleSheet("font-size: 14px");
    orbitalPeriodLineEdit = new QLineEdit("5400");
    orbitalPeriodLineEdit->setAlignment(Qt::AlignRight);
    sysCommandsLayout->addWidget(orbitalPeriodLabel,5,0,1,1,Qt::AlignLeft);
    sysCommandsLayout->addWidget(orbitalPeriodLineEdit,5,1,1,1,Qt::AlignRight);

    beginTestButton = new QPushButton("Begin Simulation");
    beginTestButton->setMinimumWidth(260);
    beginTestButton->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c; font: bold 14px; border-style: outset; border-width: 2px;}");
    sysCommandsLayout->addWidget(beginTestButton,6,0,1,2,Qt::AlignCenter);


    cmdWindowFiller = new QWidget(sysCommandsSubWidget);
    sysCommandsLayout->addWidget(cmdWindowFiller,23,0);
    sysCommandsLayout->setRowStretch(23,11000);

    connect(abortButton,SIGNAL(released()),this,SIGNAL(sendAbortShutdownSignal()));
    connect(abortButton,SIGNAL(released()),simulationTimer,SLOT(stop()));
    //connect(abortButton,SIGNAL(released()),processTimer,SLOT(stop()));
    //connect(abortButton,SIGNAL(released()),transmitTimer,SLOT(stop()));
    //connect(abortButton,SIGNAL(released()),offsetTimer,SLOT(stop()));
    connect(beginProcessButton,SIGNAL(released()),this,SIGNAL(sendBeginProcessSignal()));
    connect(beginTransmissionButton,SIGNAL(released()),this,SIGNAL(sendBeginTransmittingDataSignal()));
    connect(beginTestButton,SIGNAL(released()),this,SLOT(beginTestButton_pressed()));
    connect(beginTestButton,SIGNAL(released()),this,SLOT(startTest_triggered()));

    connect(abortButton,SIGNAL(released()),this,SLOT(abortButton_pressed()));
    connect(beginProcessButton,SIGNAL(released()),this,SLOT(beginProcessButton_pressed()));
    connect(beginTransmissionButton,SIGNAL(released()),this,SLOT(beginTransmittingButton_pressed()));
    //connect(beginTestButton,SIGNAL(released()),this,SLOT(beginTestButton_pressed()));

    connect(abortButton,SIGNAL(released()),orbitAnimation,SLOT(stopAnimation()));


    hideCommands();

    sysCommandsSubWidget->setLayout(sysCommandsLayout);

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
    //qDebug() << PBVal;
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
    //clearSystemTab();
    sysID = systemID;
    //setupSysPensandBrushes();
    switch(sysID)
    {
    case 0: //No system id given
    {

        break;
    }
    case 1: //MSP430/FPGA system
    {
        setStatusBarText("Monitoring MSP430/FPGA System:");

        setSysTabHeader(1,0,"<B>State:</B>");

        setSysTabLabels(1,2,"System State:","0");

        setSysTabHeader(2,3,"<B>Power</B>");

        setSysTabLabels(2,5,"Relay:","Open");
        setSysTabLabels(3,6,"5 V Switch:","Off");
        setSysTabLabels(4,7,"3.3 V Switch:","Off");
        //setSysTabLabels(5,8,"3.3 V Regulator(Quark/S.Flash):","Off");

        setSysTabHeader(3,8,"<B>Components</B>");

        setSysTabLabels(5,10,"MSP430:","LPM");
        setSysTabLabels(6,11,"FPGA:","Off");
        setSysTabLabels(7,12,"Quark:","Off");
        setSysTabLabels(8,13,"S.Flash:","Off");
        setSysTabLabels(9,14,"Servo:","Off");
        setSysTabLabels(10,15,"Servo Position:","Black Body");

        //ColorKey Button
        keyButton = new QPushButton("Color Key",this);
        sysStatusGridLayout->addWidget(keyButton,16,0,1,2);
        keyButton->setStyleSheet("QPushButton {background-color: lightgrey; font: bold 14px;}QPushButton:hover {background-color:#9c9c9c; border-style: outset; border-width: 2px;}");
        connect(keyButton,SIGNAL(released()),this,SLOT(colorKeyButton_pressed()));

        setSysTabHeader(4,16,"<B>Signals</B>");

        setSysTabLabels(11,18,"5 V SHDN:","GND");
        setSysTabLabels(12,19,"3.3 V SHDN(Quark/S.Flash):","GND");
        setSysTabLabels(13,20,"QUARK SHDN:","GND");
        setSysTabLabels(14,21,"Servo PWM Signal:","Off");


        sysStatusHeader4->setVisible(false);
        sysStatusLine4->setVisible(false);
        sysStatusStat11->setVisible(false);
        sysStatusStat12->setVisible(false);
        sysStatusStat13->setVisible(false);
        sysStatusStat14->setVisible(false);
        sysStatusVal11->setVisible(false);
        sysStatusVal12->setVisible(false);
        sysStatusVal13->setVisible(false);
        sysStatusVal14->setVisible(false);


        sysStatusFiller = new QWidget(sysStatusLowerW);
        sysStatusGridLayout->addWidget(sysStatusFiller,23,0);
        sysStatusGridLayout->setRowStretch(23,11000);


        //MSP430_FPGA_System_Diagram = new QPixmap(":myFiles/MSP430_FPGA_System.png");
        //sysDiagramScene->addPixmap(*MSP430_FPGA_System_Diagram);

        //+12V Relay
        QGraphicsTextItem *tmpTextItem = sysDiagramScene->addText("+12V Relay",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(170,40);

        //+5V Switch
        setSysDiagramRect(1,187,107,81,36,*blackPen,*redBrush);
        setSysDiagramRectGradient(1, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("+5V Switch",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(175,140);

        setSysDiagramRect(2,187,211,81,32,*blackPen,*greenBrush);
        setSysDiagramRectGradient(2, "#00DD00", "#009900");

        //+3.3V Switch
        setSysDiagramRect(3,187,320,81,32,*blackPen,*redBrush);
        setSysDiagramRectGradient(3, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("+3.3V Switch",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(165,350);

        //FPGA
        setSysDiagramRect(4,331,3,55,55,*blackPen,*redBrush);
        setSysDiagramRectGradient(4, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("FPGA",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(333,55);

        //MSP430
        setSysDiagramRect(5,331,195,55,55,*blackPen,*blueBrush);
        setSysDiagramRectGradient(5, "#0000DD", "#000099");
        tmpTextItem = sysDiagramScene->addText("MSP430",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(322,247);

        //Quark
        setSysDiagramRect(6,331,322,42,28,*blackPen,*redBrush);
        setSysDiagramRectGradient(6, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("Quark",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(323,347);

        //S.Flash
        setSysDiagramRect(7,331,386,55,28,*blackPen,*redBrush);
        setSysDiagramRectGradient(7, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("S.Flash",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(326,412);

        //Servo
        setSysDiagramEli(1,331,89,64,64,*blackPen,*redBrush);
        setSysDiagramEliGradient(1, "#DD0000", "#990000");
        tmpTextItem = sysDiagramScene->addText("Servo",QFont("Times",12,QFont::Bold,false));
        tmpTextItem->setPos(335,150);

        sysDiagramScene->addItem(sysDiagramEllipse1Text);


        setSysDiagramLine(1,212,30,250,15,*redPen);

        //Quark triangle shape
        sysDiagramScene->addLine(374,336,389,322,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),2,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addLine(374,336,389,350,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),2,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addLine(389,322,389,350,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),2,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //+12V relay shape
        sysDiagramScene->addEllipse(201,28,8,8,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addEllipse(250,27,8,8,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addEllipse(236,7,8,8,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addRect(181,2,92.5,40,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //line from +12V relay to FPGA
        sysDiagramScene->addLine(260,31,330,31,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //From +12V to relay
        sysDiagramScene->addLine(100,32,199,32,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        tmpTextItem = sysDiagramScene->addText("+12 V",QFont("Times",18,QFont::Bold,false));
        tmpTextItem->setPos(10,13);

        //From +5V to switch
        sysDiagramScene->addLine(100,125,186,125,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        tmpTextItem = sysDiagramScene->addText("+5 V",QFont("Times",18,QFont::Bold,false));
        tmpTextItem->setPos(25,103);

        //From +5 switch to Servo
        sysDiagramScene->addLine(270,125,330,125,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //From +3.3V to MSP430
        sysDiagramRect2->setVisible(false);
        sysDiagramScene->addLine(100,225,330,225,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        tmpTextItem = sysDiagramScene->addText("+3.3 V",QFont("Times",18,QFont::Bold,false));
        tmpTextItem->setPos(0,205);

        //From +3.3V to switch
        sysDiagramScene->addLine(230,225,230,318,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //From switch to Quark
        sysDiagramScene->addLine(270,337,329,337,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));

        //From switch to S.Flash
        sysDiagramScene->addLine(299.5,337,299.5,400,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
        sysDiagramScene->addLine(299.5,400,329,400,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));



        //Key
        //On
//        setSysDiagramRect(8,137,485,63,19,*blackPen,*greenBrush);
//        setSysDiagramRectGradient(8, "#00DD00", "#009900");
//        //Off
//        setSysDiagramRect(9,320,485,63,19,*blackPen,*redBrush);
//        setSysDiagramRectGradient(9, "#DD0000", "#990000");
//        //AM
//        setSysDiagramRect(10,137,525,63,19,*blackPen,*yellowBrush);
//        setSysDiagramRectGradient(10, "#DDDD00", "#999900");
//        //LPM
//        setSysDiagramRect(11,320,525,63,19,*blackPen,*blueBrush);
//        setSysDiagramRectGradient(11, "#0000DD", "#000099");

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
            //sysStatusGridLayout->removeWidget(sysStatusStat15);delete(sysStatusStat15);
            //sysStatusGridLayout->removeWidget(sysStatusVal15);delete(sysStatusVal15);
            sysStatusGridLayout->removeWidget(sysStatusFiller);delete(sysStatusFiller);
            sysStatusGridLayout->removeWidget(keyButton);disconnect(keyButton,SIGNAL(released()),this,SLOT(colorKeyButton_pressed()));delete(keyButton);
            sysDiagramScene->removeItem(sysDiagramEllipse1Text);
            sysDiagramScene->clear();
            sysID = 0;
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
    greenPen = new QPen(QColor(0,190,0));
    redPen = new QPen(Qt::red);
    blackPen->setWidth(2);
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
    if(myUART->isUARTOpen())
    {
        //Send shutdown message to MSP430
        emit sendAbortShutdownSignal();
        //Shutdown COM port
        myUART->setUARTClose();
        //Close application
    }
    close();
}

//Action taken when "Settings" is selected from menu
//  Open settings window
void MainWindow::on_actionSettings_triggered()
{
    settings = new Dialog(this);
    connect(settings,SIGNAL(saveClicked()),this,SLOT(updateLogList()));
    connect(settings,SIGNAL(saveClicked()),this,SLOT(updateImgList()));
    settings->setAttribute(Qt::WA_DeleteOnClose);
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
    //ui->actionDetect_System->setEnabled(false);
    //SetSysTab(1);
    QSettings tmpSettings("MontzThesis","GUISettingsFile");
    tmpSettings.beginGroup("Dialog");
    QVariant statusMonitor = tmpSettings.value("System Monitor Mode","false");
    tmpSettings.endGroup();
    bool monitorBool;
    if(!QString::compare(statusMonitor.toString(),"true",Qt::CaseInsensitive))
    {
        monitorBool = true;
    }
    else
    {
        monitorBool = false;
    }
    emit sendDetectSystemSignal(monitorBool);
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

void MainWindow::on_actionConnect_triggered()
{
    //Connect using values stored in registry
    switch(myUART->setUARTOpen())
    {
    case 0: //No error, connection successful.
    {
        setStatusBarVisibility(1);
        setStatusBarText("Serial Port Connected. Detect System to proceed");
        loadOrientationValues();
        ui->actionDisconnect->setEnabled(true);
        ui->actionConnect->setEnabled(false);
        ui->actionDetect_System->setEnabled(true);
        ui->actionSettings->setEnabled(false);
        break;
    }
    case 1: //Port is busy, connection failed.
    {
        setStatusBarText("Port is Busy, check settings and try again");
        break;
    }
    case 2: //Port not found, connection failed.
    {
        setStatusBarText("Port not found, check settings and try again");
        break;
    }
    case 3: //Baudrate undefined, connection failed.
    {
        setStatusBarText("Undefined Baudrate, check settings and try again");
        break;
    }
    case 4: //Data bits undefined, connection failed.
    {
        setStatusBarText("Undefined Databits, check settings and try again");
        break;
    }
    case 5: //Parity undefined, connection failed.
    {
        setStatusBarText("Undefined parity, check settings and try again");
        break;
    }
    case 6: //Stop bits undefined, connection failed.
    {
        setStatusBarText("Undefined stop bits, check settings and try again");
        break;
    }
    case 7: //Flow control undefined, connection failed.
    {
        setStatusBarText("Undefined flow control, check settings and try again");
        break;
    }
    case 8: //Error opening serial port. , connection failed.
    {
        setStatusBarText("Error opening serial port, check settings and try again");
        break;
    }
    default: //Unknown error, connection failed.
    {
        setStatusBarText("Unknown error opening serial port, check settings and try again");
        break;
    }
    }

//    //Load the saved settings and apply to
//    QSettings setting("MontzThesis","GUISettingsFile");
//    setting.beginGroup("Dialog");
//    QVariant Port = setting.value("Port","COM1");
//    QVariant BaudRate = setting.value("Baud Rate","115200");
//    QVariant Data = setting.value("Data","8 bit");
//    QVariant Parity = setting.value("Parity","none");
//    QVariant Stop = setting.value("Stop","1 bit");
//    QVariant FlowControl = setting.value("Flow Control","none");

//    QVariant SystemMonitorMode = setting.value("System Monitor Mode", true);
//    setting.endGroup();

//    //Output saved setting values to qDebug()
//    qDebug() << "Port: " << Port.toString();
//    qDebug() << "BaudRate: " << BaudRate.toString();
//    qDebug() << "Data: " << Data.toString();
//    qDebug() << "Parity: " << Parity.toString();
//    qDebug() << "Stop: " << Stop.toString();
//    qDebug() << "FlowControl: " << FlowControl.toString();



//    //Setup port...
//    Q_FOREACH(QSerialPortInfo tmpPort, QSerialPortInfo::availablePorts())
//    {
//        if(!QString::compare(tmpPort.portName(),Port.toString(),Qt::CaseSensitive))
//        {
//            qDebug() << "Found it";
//            if(tmpPort.isBusy())
//            {
//                qDebug() << "Busy";
//                MainWindow::setStatusBarText("Port is Busy, check settings and try again");
//            }
//            else
//            {
//                qDebug() << "Not Busy";
//                qDebug() << "Attempting to connect";

//                mySerialPort->setPort(tmpPort);

//                //Set BaudRate
//                if(!QString::compare(BaudRate.toString(),"110",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(110);
//                else if(!QString::compare(BaudRate.toString(),"300",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(300);
//                else if(!QString::compare(BaudRate.toString(),"600",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(600);
//                else if(!QString::compare(BaudRate.toString(),"1200",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud1200);
//                else if(!QString::compare(BaudRate.toString(),"2400",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud2400);
//                else if(!QString::compare(BaudRate.toString(),"4800",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud4800);
//                else if(!QString::compare(BaudRate.toString(),"9600",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud9600);
//                else if(!QString::compare(BaudRate.toString(),"14400",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(14400);
//                else if(!QString::compare(BaudRate.toString(),"19200",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud19200);
//                else if(!QString::compare(BaudRate.toString(),"38400",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud38400);
//                else if(!QString::compare(BaudRate.toString(),"56000",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(56000);
//                else if(!QString::compare(BaudRate.toString(),"57600",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud57600);
//                else if(!QString::compare(BaudRate.toString(),"115200",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(QSerialPort::Baud115200);
//                else if(!QString::compare(BaudRate.toString(),"128000",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(128000);
//                else if(!QString::compare(BaudRate.toString(),"256000",Qt::CaseInsensitive))
//                    mySerialPort->setBaudRate(256000);
//                else
//                {
//                    qDebug() << "Failed to set baud rate";
//                    break;
//                }
//                qDebug() << mySerialPort->baudRate();

//                //Set Data bits
//                switch(Data.toInt())
//                {
//                    case 7: mySerialPort->setDataBits(QSerialPort::Data7);qDebug() << "7 Data Bits";break;
//                    case 8: mySerialPort->setDataBits(QSerialPort::Data8);qDebug() << "8 Data Bits";break;
//                    default: qDebug() << "Failed to set data bits"; break;
//                }

//                //Set Parity bits
//                if(!QString::compare(Parity.toString(),"none",Qt::CaseInsensitive))
//                    mySerialPort->setParity(QSerialPort::NoParity);
//                else if(!QString::compare(Parity.toString(),"odd",Qt::CaseInsensitive))
//                    mySerialPort->setParity(QSerialPort::OddParity);
//                else if(!QString::compare(Parity.toString(),"even",Qt::CaseInsensitive))
//                    mySerialPort->setParity(QSerialPort::EvenParity);
//                else if(!QString::compare(Parity.toString(),"mark",Qt::CaseInsensitive))
//                    mySerialPort->setParity(QSerialPort::MarkParity);
//                else if(!QString::compare(Parity.toString(),"space",Qt::CaseInsensitive))
//                    mySerialPort->setParity(QSerialPort::SpaceParity);
//                else
//                {
//                    qDebug() << "Failed to set parity";
//                    break;
//                }

//                //Set Stop bits
//                if(!QString::compare(Stop.toString(),"1 bit",Qt::CaseInsensitive))
//                    mySerialPort->setStopBits(QSerialPort::OneStop);
//                else if(!QString::compare(Stop.toString(),"1.5 bit",Qt::CaseInsensitive))
//                    mySerialPort->setStopBits(QSerialPort::OneAndHalfStop);
//                else if(!QString::compare(Stop.toString(),"2 bit",Qt::CaseInsensitive))
//                    mySerialPort->setStopBits(QSerialPort::TwoStop);
//                else
//                {
//                    qDebug() << "Failed to set Stop bits";
//                    break;
//                }

//                //Set Flow Control
//                if(!QString::compare(FlowControl.toString(),"none",Qt::CaseInsensitive))
//                    mySerialPort->setFlowControl(QSerialPort::NoFlowControl);
//                else if(!QString::compare(FlowControl.toString(),"hardware",Qt::CaseInsensitive))
//                    mySerialPort->setFlowControl(QSerialPort::HardwareControl);
//                else if(!QString::compare(FlowControl.toString(),"Xon/Xoff",Qt::CaseInsensitive))
//                    mySerialPort->setFlowControl(QSerialPort::SoftwareControl);
//                else
//                {
//                    qDebug() << "Failed to set Flow control";
//                    break;
//                }
//                mySerialPort->open(QIODevice::ReadWrite);
//                //mySerialPort->write("Hello");

//                ui->actionDisconnect->setEnabled(true);
//                ui->actionConnect->setEnabled(false);
//                ui->actionDetect_System->setEnabled(true);
//                ui->actionSettings->setEnabled(false);
//                setStatusBarVisibility(1);
//                setStatusBarText("Serial Port Connected. Detect System to proceed");

//            }
//            break;
//        }
//    }

//    qDebug() << mySerialPort->portName();

}

void MainWindow::on_actionDisconnect_triggered()
{
    //offsetTimer->stop();
    //processTimer->stop();
    //transmitTimer->stop();
    disconnectUART();
    hideCommands();
}

void MainWindow::disconnectUART()
{

    myUART->setUARTClose();
    ui->actionDisconnect->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDetect_System->setEnabled(false);
    ui->actionSettings->setEnabled(true);
    setStatusBarVisibility(0);
    setStatusBarText("Serial Port Disconnected. Check settings and connect again.");
    clearSystemTab();
}

void MainWindow::hideCommands()
{
    //hide Command buttons
    abortButton->hide();
    beginProcessButton->hide();
    beginTransmissionButton->hide();
    beginTestButton->hide();
    //hide labels and line edits
    numCyclesLabel->hide();
    timeToReachTxLabel->hide();
    orbitalPeriodLabel->hide();
    numCyclesLineEdit->hide();
    timeToReachTxLineEdit->hide();
    orbitalPeriodLineEdit->hide();

}

void MainWindow::showCommands()
{
    //show Command buttons
    abortButton->show();
    beginProcessButton->show();
    beginTransmissionButton->show();
    beginTestButton->show();
    //show labels and line edits
    numCyclesLabel->show();
    timeToReachTxLabel->show();
    orbitalPeriodLabel->show();
    numCyclesLineEdit->show();
    timeToReachTxLineEdit->show();
    orbitalPeriodLineEdit->show();

}

//***************************************
//* Slots for handling incoming messages
//***************************************
void MainWindow::errorShutdownSlot(int statusByte)
{
    /*TODO: status bar message saying error encountered
     *      Update system status
     *      reset orbital diagram to idle state
     *      reset the orientation data to be sent */
    updateStatus(statusByte);
    setStatusBarText("Error encountered, system shut down.");
}

void MainWindow::ackSlot(int statusByte)
{
    //TODO: Update system status
    //      Update status bar message
    updateStatus(statusByte);
    setStatusBarText("ACK received");
}

void MainWindow::statusSlot(int sID, int statusByte)
{
    //TODO: If sysID is 0 or unknown value, call the "SetSysTab" function and showcommands(), update status bar text
    //      Update the system status.
    //      Update status bar message (clear it?)
    if(sysID == 0)
    {
        SetSysTab(sID);
        showCommands();
        ui->actionDetect_System->setEnabled(false);
        switch(sID)
        {
        case 1:setStatusBarText("MSP430/FPGA system detected. Choose command to continue");break;
        case 2:setStatusBarText("Raspberry Pi system detected. Choose command to continue");break;
        case 3:setStatusBarText("(other?) system detected. Choose command to continue");break;
        default:break;
        }
    }
    else
        setStatusBarText("");

    updateStatus(statusByte);
}

void MainWindow::reqOrientationDataSlot(int statusByte)
{
    //TODO: update system status
    //      call function that sends the next orientation data
    //      Update status bar message
    updateStatus(statusByte);

    setStatusBarText("Orientation Data Requested");

    OrientationFunction(false);
}

void MainWindow::dataTransferSignal(int statusByte, QByteArray payload)
{
    //TODO: update system status
    //      If first data packet, change statusbar visibility
    //      If last data packet, change statusbar visibility
    //      If not last data packet, update the status bar progress bar
    //      Update status bar message
    bool OK;

    int packetNumber = payload.left(2).toHex().toInt(&OK,16);
    int packetsTotal = payload.mid(2,2).toHex().toInt(&OK,16);

    //qDebug() << "progress bar val: " << ((double)packetNumber/(double)packetsTotal)*100.0;

    setStatusBarProgressBarValue(((double)packetNumber/(double)packetsTotal)*100.0);

    if(packetNumber == packetsTotal)
    {
        //hide status bar, message data rx finished
        setStatusBarVisibility(1);
        //setStatusBarProgressBarValue(((double)packetNumber/(double)packetsTotal)*100.0);
    }
    else
    {
        //show status bar, update status bar, message data rx in progress
        setStatusBarVisibility(2);

    }
    updateStatus(statusByte);
    emit sendAckSignal();


}

void MainWindow::updateStatus(int statusByte)
{
    if(sysID == 0)//No id
    {

    }
    else if(sysID == 1)//MSP430/FPGA
    {
        //System State
        sysStatusVal1->setText(QString::number(statusByte).toLatin1().data());
        //Relay
        switch(statusByte)
        {
        case 0:case 1:case 12:case 13:case 23:case 24:case 34:case 35:case 36:case 37:
        case 38:sysDiagramScene->removeItem(sysDiagramLine1);setSysDiagramLine(1,212,30,250,15,*redPen);sysStatusVal2->setText("Open");break;//open
        default:sysDiagramScene->removeItem(sysDiagramLine1);setSysDiagramLine(1,212,30,255,23,*greenPen);sysStatusVal2->setText("Closed");break;//closed
        }
        //5 V Mosfet
        switch(statusByte)
        {
        case 0: case 1: case 2:case 12:case 13:case 14:case 15:case 23:case 24:case 25:case 26:case 34:case 35:case 36:case 37:
        case 38: sysDiagramRect1Gradient->setColorAt(0.0,"#DD0000");sysDiagramRect1Gradient->setColorAt(1.0,"#990000");sysDiagramRect1->setBrush(*sysDiagramRect1Gradient);sysStatusVal3->setText("Off");break;//off
        default: sysDiagramRect1Gradient->setColorAt(0.0,"#00DD00");sysDiagramRect1Gradient->setColorAt(1.0,"#009900");sysDiagramRect1->setBrush(*sysDiagramRect1Gradient);sysStatusVal3->setText("On");break;//on
        }
        //3.3 V Mosfet
        switch(statusByte)
        {
        case 0: case 12: case 23: case 34:
        case 38: sysDiagramRect3Gradient->setColorAt(0.0,"#DD0000");sysDiagramRect3Gradient->setColorAt(1.0,"#990000");sysDiagramRect3->setBrush(*sysDiagramRect3Gradient);sysStatusVal4->setText("Off");break;//off
        default: sysDiagramRect3Gradient->setColorAt(0.0,"#00DD00");sysDiagramRect3Gradient->setColorAt(1.0,"#009900");sysDiagramRect3->setBrush(*sysDiagramRect3Gradient);sysStatusVal4->setText("On");break;//on
        }
        //Quark
        switch(statusByte)
        {
        case 0:case 12: case 23: case 34: case 35: case 36: case 37:
        case 38: sysDiagramRect6Gradient->setColorAt(0.0,"#DD0000");sysDiagramRect6Gradient->setColorAt(1.0,"#990000");sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);sysStatusVal7->setText("Off");break;//Off
        case 1: case 2: case 3: case 13: case 14: case 24:
        case 25: sysDiagramRect6Gradient->setColorAt(0.0,"#ffc04d");sysDiagramRect6Gradient->setColorAt(1.0,"#cc8400");sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);sysStatusVal7->setText("Warming Up");break;//Warming up
        case 5: case 7: case 9: case 11: case 16: case 18: case 20: case 22: case 27: case 29: case 31:
        case 33: sysDiagramRect6Gradient->setColorAt(0.0,"#d3d3d3");sysDiagramRect6Gradient->setColorAt(1.0,"#545454");sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);sysStatusVal7->setText("Idle");break;//Idle
        case 4: case 8: case 15: case 19: case 26:
        case 30: sysDiagramRect6Gradient->setColorAt(0.0,"#3f3f3f");sysDiagramRect6Gradient->setColorAt(1.0,"#000000");sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);sysStatusVal7->setText("Doing FFC");break; // Doing FFC
        case 6: case 10: case 17: case 21: case 28: case 32:
        default: sysDiagramRect6Gradient->setColorAt(0.0,"#ffff7f");sysDiagramRect6Gradient->setColorAt(1.0,"#ffff7f");sysDiagramRect6->setBrush(*sysDiagramRect6Gradient);sysStatusVal7->setText("Capturing Image");break; // Capturing Image
        }
        //SFLASH
        switch(statusByte)
        {
        case 0: case 12: case 23: case 34:
        case 38: sysDiagramRect7Gradient->setColorAt(0.0,"#DD0000");sysDiagramRect7Gradient->setColorAt(1.0,"#990000");sysDiagramRect7->setBrush(*sysDiagramRect7Gradient);sysStatusVal8->setText("Off");break;//Off
        case 6: case 7: case 10: case 11: case 17: case 18: case 21: case 22: case 28: case 29: case 32: case 33: case 35: case 36:
        case 37: sysDiagramRect7Gradient->setColorAt(0.0,"#7fafdd");sysDiagramRect7Gradient->setColorAt(1.0,"#4c6984");sysDiagramRect7->setBrush(*sysDiagramRect7Gradient);sysStatusVal8->setText("Busy");break;//Busy
        default: sysDiagramRect7Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramRect7Gradient->setColorAt(1.0,"#545454");sysDiagramRect7->setBrush(*sysDiagramRect7Gradient);sysStatusVal8->setText("Idle");break;//Idle
        }

        //Servo
        switch(statusByte)
        {
        case 3: case 5: case 7: case 9: case 11: case 16: case 18: case 20: case 22: case 27: case 29: case 31:
        case 33: sysDiagramEllipse1Gradient->setColorAt(0.0,"#7fafdd");sysDiagramEllipse1Gradient->setColorAt(1.0,"#4c6984");sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);sysStatusVal9->setText("Moving");sysStatusVal10->setText("Moving");sysDiagramEllipse1Text->setVisible(false);break;//Moving
        case 4: case 8: case 19:
        case 30: sysDiagramEllipse1Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramEllipse1Gradient->setColorAt(1.0,"#545454");sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);sysStatusVal9->setText("Idle");sysStatusVal10->setText("Black Body");sysDiagramEllipse1Text->setVisible(true);sysDiagramEllipse1Text->setPos(335,102);sysDiagramEllipse1Text->setHtml("<font size=\"48\"><b>B.B.</b></font>");break;//Blackbody idle
        case 6: case 17:
        case 28: sysDiagramEllipse1Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramEllipse1Gradient->setColorAt(1.0,"#545454");sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);sysStatusVal9->setText("Idle");sysStatusVal10->setText("Filter A");sysDiagramEllipse1Text->setVisible(true);sysDiagramEllipse1Text->setPos(351,102);sysDiagramEllipse1Text->setHtml("<font size=\"48\"><b>A</b></font>");break;//Filter A idle
        case 10: case 21:
        case 32: sysDiagramEllipse1Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramEllipse1Gradient->setColorAt(1.0,"#545454");sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);sysStatusVal9->setText("Idle");sysStatusVal10->setText("Filter B");sysDiagramEllipse1Text->setVisible(true);sysDiagramEllipse1Text->setPos(351,102);sysDiagramEllipse1Text->setHtml("<font size=\"48\"><b>B</b></font>");break;//Filter B idle
        default: sysDiagramEllipse1Gradient->setColorAt(0.0,"#DD0000");sysDiagramEllipse1Gradient->setColorAt(1.0,"#990000");sysDiagramEllipse1->setBrush(*sysDiagramEllipse1Gradient);sysStatusVal9->setText("Off");sysStatusVal10->setText("Black Body");sysDiagramEllipse1Text->setVisible(true);sysDiagramEllipse1Text->setPos(335,102);sysDiagramEllipse1Text->setHtml("<font size=\"48\"><b>B.B.</b></font>");break;//Blackbody off
        }

        //FPGA
        switch(statusByte)
        {
        case 0: case 1: case 12: case 13: case 23: case 24: case 34: case 35: case 36: case 37:
        case 38: sysDiagramRect4Gradient->setColorAt(0.0,"#DD0000");sysDiagramRect4Gradient->setColorAt(1.0,"#990000");sysDiagramRect4->setBrush(*sysDiagramRect4Gradient);sysStatusVal6->setText("Off");break;// off
        case 2: case 3: case 14:
        case 25: sysDiagramRect4Gradient->setColorAt(0.0,"#ffc04d");sysDiagramRect4Gradient->setColorAt(1.0,"#cc8400");sysDiagramRect4->setBrush(*sysDiagramRect4Gradient);sysStatusVal6->setText("Warming Up");break;//Warming up
        case 6: case 7: case 10: case 11: case 17: case 18: case 21: case 22: case 28: case 29: case 32:
        case 33: sysDiagramRect4Gradient->setColorAt(0.0,"#7fafdd");sysDiagramRect4Gradient->setColorAt(1.0,"#4c6984");sysDiagramRect4->setBrush(*sysDiagramRect4Gradient);sysStatusVal6->setText("Busy");break;//Busy
        default: sysDiagramRect4Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramRect4Gradient->setColorAt(1.0,"#545454");sysDiagramRect4->setBrush(*sysDiagramRect4Gradient);sysStatusVal6->setText("Idle");break;//Idle
        }

        //MSP430
        switch(statusByte)
        {
        case 0: case 12: case 23: case 34:
        case 38:sysDiagramRect5Gradient->setColorAt(0.0,"#D3D3D3");sysDiagramRect5Gradient->setColorAt(1.0,"#545454");sysDiagramRect5->setBrush(*sysDiagramRect5Gradient);sysStatusVal5->setText("LPM(Idle)");break;//LPM(Idle)
        case 35: case 36:
        case 37:sysDiagramRect5Gradient->setColorAt(0.0,"#7fafdd");sysDiagramRect5Gradient->setColorAt(1.0,"#4c6984");sysDiagramRect5->setBrush(*sysDiagramRect5Gradient);sysStatusVal5->setText("AM(Data Transfer)");break;//AM(Data Transfer)
        default: sysDiagramRect5Gradient->setColorAt(0.0,"#006600");sysDiagramRect5Gradient->setColorAt(1.0,"#003d00");sysDiagramRect5->setBrush(*sysDiagramRect5Gradient);sysStatusVal5->setText("LPM(Pwr Mgmt)");break;//LPM(Power Management)
        }
    }
    else if(sysID == 2)//R_Pi
    {

    }
    else if(sysID == 3)//Other System?
    {

    }
}

void MainWindow::startTest_triggered()
{
    bool OK;
    numCycles = numCyclesLineEdit->text().toInt(&OK,10);
    midInterval = timeToReachTxLineEdit->text().toInt(&OK,10)*1000;
    orbInterval = orbitalPeriodLineEdit->text().toInt(&OK,10)*1000;
    procInterval = orbInterval;

    if(midInterval >= orbInterval)
    {
        setStatusBarText("Error: Make sure orbital period > time to reach TX location.");
        return;
    }
    //offsetTimer->setInterval(midInterval);
    //processTimer->setInterval(orbInterval);
    //transmitTimer->setInterval(orbInterval);

    //offsetTimer->start();
    //processTimer->start();


    elapsedTime->restart();
    simulationTimer->start();

    QSettings tmpSettings("MontzThesis","GUISettingsFile");
    tmpSettings.beginGroup("Dialog");
    QVariant SystemAnimationEnabled = tmpSettings.value("Simulation Animation Enable", "true");
    tmpSettings.endGroup();

    if(!QString::compare(SystemAnimationEnabled.toString(),"true",Qt::CaseInsensitive))
        orbitAnimation->startAnimation(numCycles,timeToReachTxLineEdit->text().toInt(&OK,10),orbitalPeriodLineEdit->text().toInt(&OK,10));

    emit sendBeginProcessSignal();
    setStatusBarText("Begin process message sent");
}

void MainWindow::OrientationFunction(bool reset)
{
    if(reset)
    {
        orientationIndex = 0;
    }

    //load orientation values
    emit sendOrientationData(latValues[orientationIndex],
                             lonValues[orientationIndex],
                             aziValues[orientationIndex]);

    setStatusBarText("Orientation Data Sent");
    orientationIndex = (orientationIndex + 1)%6;
}

void MainWindow::loadOrientationValues()
{
    QSettings tmpSetting("MontzThesis","GUISettingsFile");
    tmpSetting.beginGroup("Orientation");

    latValues[0] = tmpSetting.value("Lat1A","0.0").toDouble();
    lonValues[0] = tmpSetting.value("Lon1A","0.0").toDouble();
    aziValues[0] = tmpSetting.value("Azi1A","0.0").toDouble();
    latValues[1] = tmpSetting.value("Lat1B","0.0").toDouble();
    lonValues[1] = tmpSetting.value("Lon1B","0.0").toDouble();
    aziValues[1] = tmpSetting.value("Azi1B","0.0").toDouble();
    latValues[2] = tmpSetting.value("Lat2A","0.0").toDouble();
    lonValues[2] = tmpSetting.value("Lon2A","0.0").toDouble();
    aziValues[2] = tmpSetting.value("Azi2A","0.0").toDouble();
    latValues[3] = tmpSetting.value("Lat2B","0.0").toDouble();
    lonValues[3] = tmpSetting.value("Lon2B","0.0").toDouble();
    aziValues[3] = tmpSetting.value("Azi2B","0.0").toDouble();
    latValues[4] = tmpSetting.value("Lat3A","0.0").toDouble();
    lonValues[4] = tmpSetting.value("Lon3A","0.0").toDouble();
    aziValues[4] = tmpSetting.value("Azi3A","0.0").toDouble();
    latValues[5] = tmpSetting.value("Lat3B","0.0").toDouble();
    lonValues[5] = tmpSetting.value("Lon3B","0.0").toDouble();
    aziValues[5] = tmpSetting.value("Azi3B","0.0").toDouble();

    tmpSetting.endGroup();
}

void MainWindow::offsetTimer_triggered()
{
    emit sendBeginTransmittingDataSignal();
    //transmitTimer->start();
    setStatusBarText("Begin Transmission message sent");
}

void MainWindow::processTimer_triggered()
{
//    if(cyclesLeft > 1) //If another cycle is happening.
//    {
//        emit sendBeginProcessSignal();
//        setStatusBarText("Begin process message sent");
//        cyclesLeft -= 1;
//    }
//    else
//    {
//        //processTimer->stop();
//        //transmitTimer->stop();
//        //offsetTimer->stop();
//        setStatusBarText("Simulation finished");
//    }
}

void MainWindow::transmitTimer_triggered()
{
    //emit sendBeginTransmittingDataSignal();
    //setStatusBarText("Begin Transmission message sent");
}

void MainWindow::simulationTimer_triggered()
{

    //check for end of simulation
    if(elapsedTime->hasExpired(numCycles * orbInterval))
    {
        setStatusBarText("Simulation finished");
        return;
    }

    //check for transmission timeout
    if(elapsedTime->hasExpired(midInterval))
    {
        //qDebug() << "mid int: " << midInterval;

        midInterval += orbInterval;
        //qDebug() << "mid int +: " << midInterval;
        emit sendBeginTransmittingDataSignal();
        setStatusBarText("Begin Transmission message sent");
    }

    //check for process timeout
    if(elapsedTime->hasExpired(procInterval))
    {
        procInterval += orbInterval;
        emit sendBeginProcessSignal();
        setStatusBarText("Begin process message sent");
    }

    simulationTimer->start();
}

void MainWindow::abortButton_pressed()
{
    setStatusBarText("Abort message sent. All processes ended.");
}

void MainWindow::beginProcessButton_pressed()
{
    setStatusBarText("Begin process message sent");
}

void MainWindow::beginTransmittingButton_pressed()
{
    setStatusBarText("Begin Transmission message sent");
}

void MainWindow::beginTestButton_pressed()
{
    setStatusBarText("Simulation started");

    //One second non blocking delay
    /*QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    */
}

void MainWindow::loadLog()
{

    if(logsfDir->isEmpty())
    {
        setStatusBarText("Error: No file selected");
        return;
    }

    setStatusBarText("Loading log file...");
    QFile file(*logsfDir);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream ReadFile(&file);
    QString tempFileContents;

    tempFileContents = ReadFile.readAll();

    setStatusBarText("formatting log file...");
    //Color scheme used is a variation of "SOLARIZED" from "http://ethanschoonover.com/solarized" by Ethan Schoonover
    tempFileContents.replace("RX","<font color=\"#CC0000\"><b>RX</b></font>");
    tempFileContents.replace("TX","<font color=\"green\"><b>TX</b></font>");
    tempFileContents.replace("Function:","<font color=\"#6C71C4\"><b>Function:</b></font>");
    tempFileContents.replace("SystemID:","<font color=\"#268BD2\"><b>SystemID:</b></font>");
    tempFileContents.replace("Status:","<font color=\"#2AA198\"><b>Status:</b></font>");
    tempFileContents.replace("Packet:","<font color=\"#859900\"><b>Packet:</b></font>");
    tempFileContents.replace("Current Latitude:","<font color=\"#CB4B16\"><b>Current Latitude:</b></font>");
    tempFileContents.replace("Current Longitude:","<font color=\"#DC322F\"><b>Current Longitude:</b></font>");
    tempFileContents.replace("Current Azimuth:","<font color=\"#D33682\"><b>Current Azimuth:</b></font>");
    tempFileContents.replace("Status Updates:","<font color=\"#B58900\"><b>Status Updates:</b></font>");
    tempFileContents.replace("Packet Number:","<font color=\"#00A43D\"><b>Packet Number:</b></font>");
    tempFileContents.replace("Total Packets:","<font color =\"#60CE96\"><b>Total Packets:</b></font>");
    tempFileContents.replace("NACK","<font color =\"#CC0000\"><b>NACK</b></font>");
    tempFileContents.replace("[","<font color=\"#B58900\">");//B58900
    tempFileContents.replace("]","</font>");
    tempFileContents.replace("    ","");
    tempFileContents.replace("\n","<br>");

    logsDisplayTextBrowser->document()->setHtml(tempFileContents);
    logsDisplayTextBrowser->setStyleSheet("background-color: #002B36; font-size: 14px; color: #808F8F;");

    file.close();
    setStatusBarText("Log file loaded");

}

void MainWindow::clickedOnLogFile(const QModelIndex &index)
{
    *logsfDir = logsFileModel->fileInfo(index).absoluteFilePath();
    loadLog();
}

void MainWindow::updateLogList()
{
    //logsfDir = new QString;
    QSettings tmpSett("MontzThesis","GUISettingsFile");
    tmpSett.beginGroup("Dialog");
    QString sPath = tmpSett.value("Log Save Dir", "C:/").toString() + "/";
    tmpSett.endGroup();
    //logsFileModel = new QFileSystemModel(this);
    logsFileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.comLog";
    logsFileModel->setNameFilters(filters);
    logsFileModel->setNameFilterDisables(false);
    logsListListView->setModel(logsFileModel);
    logsListListView->setRootIndex(logsFileModel->setRootPath(sPath));
}

void MainWindow::logRefreshButton_clicked()
{
    loadLog();
}

void MainWindow::zoomInButton_pressed()
{
    imgDisplayView->scale(2,2);
    zoomCount++;
}

void MainWindow::zoomOutButton_pressed()
{
    imgDisplayView->scale(1/(2.0),1/(2.0));
    zoomCount--;
}

void MainWindow::zoomResetButton_pressed()
{
    imgDisplayView->scale(1/std::pow(2.0,zoomCount),1/std::pow(2.0,zoomCount));
    zoomCount = 0;
}

void MainWindow::colormapCombo_changed(int cmIndex)
{
    myImgReader->setColormap_SLOT(cmIndex);

/*
    imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgImage()));

    //QGraphicsPixmapItem* colorbar;
//    if(colorbar->isEnabled())
//        imgDisplayScene->removeItem(colorbar);
    colorbar = imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgColorbar()));
    colorbar->moveBy(-20,110);
    //rectExists = false;
    */
    updateImage();
}

void MainWindow::loadImg()
{



    if(imgfDir->isEmpty())
    {
        setStatusBarText("Error: No file selected");
        return;
    }



    setStatusBarText("Loading imgdat file...");
//**************
//Handle image loading here


    if(!QString::compare(*imgfDir,*imgfDirOld,Qt::CaseInsensitive))
    {
        setStatusBarText("Image file already loaded");
        updateHistogram();
        return;
    }


    myImgReader->loadImgdat(*imgfDir,imgOpColormapCombo->currentIndex());

    updateImage();



/*
    //QGraphicsSceneMouseEvent
    imgDisplayScene->clear();
    imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgImage()));

//    if(colorbar->isEnabled())
//        imgDisplayScene->removeItem(colorbar);




    colorbar = imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgColorbar()));
    colorbar->moveBy(-20,110);

    QGraphicsTextItem * HighText = new QGraphicsTextItem;
    QGraphicsTextItem * LowText = new QGraphicsTextItem;

    HighText->setPos(-29,78);
    HighText->setPlainText("+");
    HighText->setScale(2);
    imgDisplayScene->addItem(HighText);

    LowText->setPos(-31,344);
    LowText->setPlainText("-");
    LowText->setScale(3);
    imgDisplayScene->addItem(LowText);

    //qDebug() << imgDisplayView->sceneRect();

    imgDisplayView->setSceneRect(-21,0,671,480);

    rectExists = false;
    //connect()
*/

    updateHistogram();


    //**************
    setStatusBarText("Image file loaded");
    imgLoaded = true;

}

void MainWindow::clickedOnImgFile(const QModelIndex &index)
{
    *imgfDirOld = *imgfDir;
    *imgfDir = imgFileModel->fileInfo(index).absoluteFilePath();
    imgMinScaler->setValue(0);
    imgMaxScaler->setValue(255);
    if(!imgLoaded)
    {
    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),myImgReader,SLOT(minImgScaleChanged(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),this,SLOT(minSliderMoved(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),myImgReader,SLOT(maxImgScaleChanged(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),this,SLOT(maxSliderMoved(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),this,SLOT(moveMinSlider(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),this,SLOT(moveMaxSlider(qreal)));
    connect(imgStatsHistoScene,SIGNAL(sceneMouseDoubleClicked()),this,SLOT(resetColormap()));
    }
    loadImg();
    imgMaxScaler->setEnabled(true);
    imgMinScaler->setEnabled(true);
    imgOpColorscaleReset->setEnabled(true);
    colorbar->setEnabled(true);

//    if(imgLoaded = false)
//    {
//    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),myImgReader,SLOT(minImgScaleChanged(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),this,SLOT(minSliderMoved(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),myImgReader,SLOT(maxImgScaleChanged(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),this,SLOT(maxSliderMoved(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMousePressed(qreal)),this,SLOT(moveMinSlider(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMouseReleased(qreal)),this,SLOT(moveMaxSlider(qreal)));
//    connect(imgStatsHistoScene,SIGNAL(sceneMouseDoubleClicked()),this,SLOT(resetColormap()));
//    }
}

void MainWindow::updateImgList()
{
    //logsfDir = new QString;
    QSettings tmpSett("MontzThesis","GUISettingsFile");
    tmpSett.beginGroup("Dialog");
    QString sPath = tmpSett.value("Image Save Dir", "C:/").toString() + "/";
    tmpSett.endGroup();
    //logsFileModel = new QFileSystemModel(this);
    imgFileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters;
    filters << "*.imgdata";
    imgFileModel->setNameFilters(filters);
    imgFileModel->setNameFilterDisables(false);
    imgListListView->setModel(imgFileModel);
    imgListListView->setRootIndex(imgFileModel->setRootPath(sPath));
}

void MainWindow::updateHistogram()
{
    histo = myImgReader->getHistogram();
    int max = 0;
    int i;
    for(i = 0; i < 256; i++) if(max<histo[i]) max = histo[i];

    int maxy = imgStatsHistoView->height();

    int val;

    imgStatsHistoScene->clear();
    for(i = 0; i<256;i++)
    {
       val = histo[i];
       val = (maxy - 30)*val/max;
       imgStatsHistoScene->addLine(i,maxy-10,i,maxy-val-10,QPen(QColor(i,0,255-i)));
    }

    QGraphicsTextItem * maxText = new QGraphicsTextItem;
    QGraphicsTextItem * minText = new QGraphicsTextItem;
    QGraphicsTextItem * titleText = new QGraphicsTextItem;
    imgHistText = new QGraphicsTextItem;
    maxText->setPos(0,188);
    maxText->setPlainText(imgStatsMinLabel->text().remove(3,6));
    imgStatsHistoScene->addItem(maxText);

    minText->setPos(160,188);
    minText->setPlainText(imgStatsMaxLabel->text().remove(3,6));
    imgStatsHistoScene->addItem(minText);

    titleText->setPos(85,5);
    titleText->setPlainText("Image Histogram");
    imgStatsHistoScene->addItem(titleText);

    imgHistText->setPos(85,25);
    imgStatsHistoScene->addItem(imgHistText);

    //minRectHistItem = imgStatsHistoScene->addRect(-imgStatsHistoScene->width(),0,imgStatsHistoScene->width(),imgStatsHistoScene->height()+50,QPen(QColor(150,150,150)),QBrush(QColor(150,150,150),Qt::SolidPattern));

    minRectHistItem = imgStatsHistoScene->addRect(-700,0,700,500,QPen(QColor(150,150,150)),QBrush(QColor(150,150,150),Qt::SolidPattern));
    minRectHistItem->setZValue(-2);
    minRectHistItem->setPos(imgMinScaler->value(),0);
    //minRectHistItem->setPos(50,0);

    //maxRectHistItem = imgStatsHistoScene->addRect(0,0,imgStatsHistoScene->width(),imgStatsHistoScene->height()+50,QPen(QColor(150,150,150)),QBrush(QColor(150,150,150),Qt::SolidPattern));

    maxRectHistItem = imgStatsHistoScene->addRect(0,0,700,500,QPen(QColor(150,150,150)),QBrush(QColor(150,150,150),Qt::SolidPattern));
    maxRectHistItem->setZValue(-2);
    maxRectHistItem->setPos(imgMaxScaler->value(),0);


}


void MainWindow::setColorScheme()
{
//Color scheme used is a variation of "SOLARIZED" from "http://ethanschoonover.com/solarized" by Ethan Schoonover
    //Read in QSS file
    QString myStyleSheet;
    QFile file(":myFiles/stylesheet.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        myStyleSheet = file.readAll();
        file.close();
    }

    //Set stylesheet
    setStyleSheet(myStyleSheet);
}

void MainWindow::InvertingCheckbox_released()
{
    updateImage();

/*    imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgImage()));

//    if(colorbar->isEnabled())
//        imgDisplayScene->removeItem(colorbar);
    colorbar = imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgColorbar()));
    colorbar->moveBy(-20,110);
    //rectExists = false;
*/
}


void MainWindow::scenePressed_endSlot(int pixelValue, QPointF clickPosition, int histLocation)
{


    QPen myPen(QColor(0,255,255));
    QBrush myBrush(QColor(255,0,255),Qt::SolidPattern);

    //imgDisplayPointerRect = imgDisplayScene->addRect(x,y,rectSize,rectSize,QPen(QColor(100,100,100)),QBrush(QColor(100,100,100),Qt::transparent));

    if((clickPosition.x() < 0) | (clickPosition.y() < 0) | (clickPosition.x() > imgDisplayScene->width()) | (clickPosition.y() > imgDisplayScene->height()))
        return;

    if(rectExists)
    {
        //imgStatsHistoScene->removeItem(imgHistogramLine);
    }
    //imgDisplayScene->clear();




    updateImage();

    imgDisplayPointerRect = imgDisplayScene->addRect(clickPosition.x(),clickPosition.y(),5.0,5.0,myPen,myBrush);




    imgHistogramLine = imgStatsHistoScene->addLine(histLocation,50,histLocation,imgStatsHistoView->height()-12,QPen(QBrush(QColor(0,0,0),Qt::SolidPattern),1.0,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));
    //imgHistogramLine->setZValue(-1);

    imgColorbarLine = imgDisplayScene->addLine(-19,368-histLocation,-7,368-histLocation,QPen(QBrush(QColor(255,255,255),Qt::SolidPattern),3.0,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin));




    QString tmpString = "Selection Value: " + QString::number(pixelValue,10);

    imgHistText->setPlainText(tmpString);

    rectExists = true;

}


void MainWindow::updateImage()
{
    imgDisplayScene->clear();
    imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgImage()));
    colorbar = imgDisplayScene->addPixmap(QPixmap::fromImage(*myImgReader->getImgColorbar()));
    colorbar->moveBy(-20,110);
    colorbar->setZValue(-3);

    if(rectExists)
    {
        imgStatsHistoScene->removeItem(imgHistogramLine);
    }

    QGraphicsTextItem * HighText = new QGraphicsTextItem;
    QGraphicsTextItem * LowText = new QGraphicsTextItem;

    HighText->setPos(-29,78);
    HighText->setPlainText("+");
    HighText->setScale(2);
    imgDisplayScene->addItem(HighText);

    LowText->setPos(-31,344);
    LowText->setPlainText("-");
    LowText->setScale(3);
    imgDisplayScene->addItem(LowText);
    rectExists = false;
}

void MainWindow::minSliderMoved(int value)
{
    minRectHistItem->setPos(value,0);
}

void MainWindow::maxSliderMoved(int value)
{
    maxRectHistItem->setPos(value,0);
}

void MainWindow::minSliderMoved(qreal value)
{
    minRectHistItem->setPos((int)value,0);
}

void MainWindow::maxSliderMoved(qreal value)
{
    maxRectHistItem->setPos((int)value,0);
}

void MainWindow::moveMinSlider(qreal val)
{
    if((int)val > 255)
        imgMinScaler->setValue(255);
    else if((int)val < 0)
        imgMinScaler->setValue(0);
    else
        imgMinScaler->setValue((int)val);
}

void MainWindow::moveMaxSlider(qreal val)
{
    if((int)val > 255)
        imgMaxScaler->setValue(255);
    else if((int)val < 0)
        imgMaxScaler->setValue(0);
    else
        imgMaxScaler->setValue((int)val);
}

void MainWindow::resetColormap()
{

   myImgReader->minImgScaleChanged(0.0);
   minSliderMoved(0);
   imgMinScaler->setValue(0);
   myImgReader->maxImgScaleChanged(255.0);
   maxSliderMoved(255);
   imgMaxScaler->setValue(255);
   rectExists = false;
}

void MainWindow::saveImg()
{
    //Load the saved settings and apply to
    QSettings setting("MontzThesis","GUISettingsFile");
    setting.beginGroup("Dialog");
    QVariant SaveFileDir = setting.value("PNG CSV Save Dir",".\\Saves\\");
    setting.endGroup();

    QString fileDirectory = QFileDialog::getSaveFileName(this,tr("Save File"),SaveFileDir.toString(),"CSV Files (*.csv);;BMP Files (*.bmp);;JPG Files (*.jpg);;JPEG Files (*.jpeg);;PNG Files (*.png);;PPM Files (*.ppm);;XBM Files (*.xbm);;XPM Files (*.xpm)");

    QMessageBox msgBox;
    msgBox.setText(tr("Choose the style to save image in."));
    msgBox.setWindowTitle(tr("Image Style"));
    QAbstractButton* pButtonSimple = msgBox.addButton(tr("Original Scale"),QMessageBox::YesRole);
    QAbstractButton* pButtonAsDisplayed = msgBox.addButton(tr("As Displayed"),QMessageBox::YesRole);
    QAbstractButton* pButtonWithStats = msgBox.addButton(tr("Include Statistics"),QMessageBox::YesRole);


    if(!QString::compare(fileDirectory.right(3),"csv"))
    {
        emit saveCsvFile(fileDirectory);
    }
    else if(!QString::compare(fileDirectory.right(3),"bmp"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"BMP",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"jpg"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"JPG",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"jpeg"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"JPEG",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"png"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"PNG",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"ppm"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"PPM",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"xbm"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"XBM",100);
        file.close();
    }
    else if(!QString::compare(fileDirectory.right(3),"xpm"))
    {

        msgBox.exec();

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QPixmap displayGrab;

        if(msgBox.clickedButton()==pButtonWithStats)//reply == QMessageBox::Yes)
        {
            QRect grabRect = imgDisplayView->rect();
            grabRect.setWidth(grabRect.width()+290);
            grabRect.moveTopLeft(QPoint(264,105));
            displayGrab = QWidget::grab(grabRect);
        }
        else if(msgBox.clickedButton()==pButtonAsDisplayed)
            displayGrab = QPixmap::grabWidget(imgDisplayView);
        else if(msgBox.clickedButton()==pButtonSimple)
            displayGrab = QPixmap::fromImage(*myImgReader->getImgImage());

        imgDisplayView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        imgDisplayView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        QFile file(fileDirectory);
        file.open(QIODevice::WriteOnly);
        displayGrab.save(&file,"XPM",100);
        file.close();
    }
}

void MainWindow::colorKeyButton_pressed()
{
    if(this->findChild<ColorKey*>("colorKeyDialog"))
        return;
    ColorKey colorKeyDialog(this);

    colorKeyDialog.setObjectName("colorKeyDialog");
    colorKeyDialog.move(this->pos().x()+75,this->pos().y()+516);
    colorKeyDialog.show();
    colorKeyDialog.exec();

}

void MainWindow::moveEvent(QMoveEvent * event)
{


//    int oldX, newX, oldY, newY;
//    oldX = event->oldPos().x();
//    newX = event->pos().x();
//    oldY = event->oldPos().y();
//    newY = event->pos().y();

    QMainWindow::moveEvent( event );

    if(!this->findChild<ColorKey*>("colorKeyDialog"))
    {
        return;
    }
    ColorKey *colorKeyDialog = this->findChild<ColorKey*>("colorKeyDialog");
    QPoint dxy = colorKeyDialog->getDistances();
    colorKeyDialog->move(this->pos().x()+75,this->pos().y()+516);

//    colorKeyDialog->move(colorKeyDialog->pos().x()+(newX - oldX),colorKeyDialog->pos().y()+(newY - oldY));
}
