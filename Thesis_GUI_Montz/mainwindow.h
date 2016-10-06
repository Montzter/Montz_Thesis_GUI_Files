#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Dialog.h"
#include <QtWidgets>
#include <QSerialPort>
#include "myuart.h"
#include "orbitalanimationwidget.h"
#include "imgdatreader.h"
#include "mycustomscene.h"

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
    void InitializeCommandsWidget();
    int getStatusBarProgressBarValue();
    void setStatusBarVisibility(int status);
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
    void moveEvent(QMoveEvent * event);
    void disconnectUART();
    ~MainWindow();

signals:
    void showSettings();

    void sendAbortShutdownSignal();
    void sendAckSignal();
    void sendDetectSystemSignal(bool);
    void sendBeginProcessSignal();
    void sendBeginTransmittingDataSignal();
    void sendOrientationData(double,double,double);

    void saveCsvFile(QString);

public slots:
    void setStatusBarText(char LabelString[]);
    void refreshStatusBarText();
    void setStatusBarProgressBarValue(int PBVal);
    void setRXBlink();
    void setTXBlink();

    void scenePressed_endSlot(int pixelValue, QPointF clickPosition, int histLocation);

    void errorShutdownSlot(int statusByte);
    void ackSlot(int statusByte);
    void statusSlot(int sID, int statusByte);
    void reqOrientationDataSlot(int statusByte);
    void dataTransferSignal(int statusByte, QByteArray payload);

    void moveMinSlider(qreal val);
    void moveMaxSlider(qreal val);

private slots:
    void on_actionClose_triggered();
    void on_actionSettings_triggered();
    void on_actionDetect_System_triggered();
    void startTest_triggered();

    void resetRXIndicator();
    void resetTXIndicator();
    void refitScene();

    void offsetTimer_triggered();
    void processTimer_triggered();
    void transmitTimer_triggered();
    void simulationTimer_triggered();

    void colorKeyButton_pressed();

    void abortButton_pressed();
    void beginProcessButton_pressed();
    void beginTransmittingButton_pressed();
    void beginTestButton_pressed();


    void zoomInButton_pressed();
    void zoomOutButton_pressed();
    void zoomResetButton_pressed();


    void colormapCombo_changed(int cmIndex);
    void InvertingCheckbox_released();


    void clickedOnLogFile(const QModelIndex &index);
    void logRefreshButton_clicked();
    void updateLogList();
    void on_actionConnect_triggered();

    void clickedOnImgFile(const QModelIndex &index);
    void updateImgList();
    void loadImg();

    void updateImage();

    void on_actionDisconnect_triggered();

    void minSliderMoved(int value);
    void maxSliderMoved(int value);
    void minSliderMoved(qreal value);
    void maxSliderMoved(qreal value);
    void resetColormap();
    void saveImg();

private:
    Ui::MainWindow *ui;

    void setColorScheme();

    int numCycles;
    int midInterval;
    int orbInterval;
    int procInterval;
    QElapsedTimer *elapsedTime;
    QTimer *simulationTimer;

    //QTimer *processTimer;
    //QTimer *transmitTimer;
    //QTimer *offsetTimer;



    void hideCommands();
    void showCommands();
    void updateStatus(int statusByte);
    void OrientationFunction(bool reset);
    int orientationIndex;
    void loadOrientationValues();
    double latValues[6];
    double lonValues[6];
    double aziValues[6];

    Dialog *settings;
    int sysID; //0:No id, 1:MSP430/FPGA 2:R_Pi 3:Other System?

    //Objects for UART
    MyUART *myUART;
    //QSerialPort *mySerialPort;


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
    QWidget *logsTabBorder;
    QVBoxLayout *logsTabBorderLayout;
    QSplitter *logsSplitter;

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
                QPushButton *keyButton;

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
                QGraphicsTextItem *sysDiagramEllipse1Text;

                QRadialGradient *sysDiagramEllipse1Gradient;

            //Right collumn of system tab splitter
            QWidget *sysCommandsW;
            QVBoxLayout *sysCommandsVLayout;
            QLabel *sysCommandsLbl;
            QWidget *sysCommandsSubWidget;
            QGridLayout *sysCommandsLayout;

                QPushButton *abortButton;
                QPushButton *beginProcessButton;
                QPushButton *beginTransmissionButton;
                QPushButton *beginTestButton;

                QLabel *numCyclesLabel;
                QLabel *timeToReachTxLabel;
                QLabel *orbitalPeriodLabel;

                QLineEdit *numCyclesLineEdit;
                QLineEdit *timeToReachTxLineEdit;
                QLineEdit *orbitalPeriodLineEdit;

                QIntValidator *gtzIntValidator;

                QWidget *cmdWindowFiller;

            QLabel *sysSimulationLbl;
            QWidget *sysSimulationWidget;
            QVBoxLayout *sysSimulationLayout;
                OrbitalAnimationWidget *orbitAnimation;
                QWidget *sysSimulationFiller;

    //Images Tab Widgets
    //imgreader items
    ImgdatReader *myImgReader;

    QWidget *cImagesTab;
    QGridLayout *imgGridLayout;
        //Left collumn
        QWidget *imgListLeftWidget;
        QVBoxLayout *imgListLeftLayout;
        QLabel *imgListLabel;
        QWidget *imgListW;
        QVBoxLayout *imgListLayout;
        QListView *imgListListView;
        QFileSystemModel *imgFileModel;
        QString *imgfDir;
        QString *imgfDirOld;
        //void loadLog();

        //Central collumn
        QWidget *imgDisplayCentralWidget;
        QVBoxLayout *imgDisplayCentralLayout;
        QLabel *imgDisplayLabel;
        QWidget *imgDisplayW;
        QVBoxLayout *imgDisplayLayout;
        QGraphicsView *imgDisplayView;
        myCustomScene *imgDisplayScene;
        QGraphicsRectItem *imgDisplayPointerRect;
        QGraphicsLineItem *imgHistogramLine;
        QGraphicsLineItem *imgColorbarLine;
        QGraphicsTextItem *imgHistText;
        QGraphicsPixmapItem *colorbar;
        bool rectExists;
        bool imgLoaded;
        //QGraphicsScene *imgDisplayScene;


        QLabel *imgOptionsLabel;
        QWidget *imgOptionsW;
        //QHBoxLayout *imgOptionsLayout;
        QGridLayout *imgOptionsLayout;
        QPushButton *imgOpZoomIn;
        QPushButton *imgOpZoomOut;
        QPushButton *imgOpZoomReset;
        int zoomCount;
        QLabel *imgOpColormapLabel;
        QComboBox *imgOpColormapCombo;
        QCheckBox *imgOpInvertCheckBox;
        QSlider *imgMinScaler;
        QSlider *imgMaxScaler;
        QLabel *imgMinScalerLabel;
        QLabel *imgMaxScalerLabel;
        QPushButton *imgOpColorscaleReset;
        QPushButton *imgSaveButton;

        //Right collum
        QWidget *imgStatsLeftWidget;
        QVBoxLayout *imgStatsLeftLayout;

        QLabel *imgStatsLabel;
        QWidget *imgStatsW;
        QVBoxLayout *imgStatsLayout;
        QLabel *imgStatsDateLabel;
        QLabel *imgStatsImageTypeLabel;
        QLabel *imgStatsLatLabel;
        QLabel *imgStatsLonLabel;
        QLabel *imgStatsAziLabel;
        QLabel *imgStatsWidthLabel;
        QLabel *imgStatsHeightLabel;
        QLabel *imgStatsBytesPerPixelLabel;
        QLabel *imgStatsOrignialDataFormatLabel;
        QLabel *imgStatsCameraPartNumLabel;
        QLabel *imgStatsCameraUsedLabel;
        QLabel *imgStatsLensUsedLabel;
        QLabel *imgStatsFovLabel;
        QLabel *imgStatsMinLabel;
        QLabel *imgStatsMaxLabel;
        QLabel *imgStatsAvgLabel;
        QGraphicsView *imgStatsHistoView;
        myCustomScene *imgStatsHistoScene;
        //QGraphicsScene *imgStatsHistoScene;
        int *histo;
        void updateHistogram();
        QWidget *imgStatsFillerWidget;
        QGraphicsRectItem *minRectHistItem;
        QGraphicsRectItem *maxRectHistItem;


    //Logs Tab Widgets
    QWidget *cLogsTab;
    QVBoxLayout *logsGridLayout;
    QLabel *logsList;
    QLabel *logsDisplay;
            //Left collumn of logs tab splitter
            QWidget *logsListW;
            QVBoxLayout *logsListVLayout;
            QLabel *logsListLbl;
            QWidget *logsListLowerW;
            QListView *logsListListView;
            QFileSystemModel *logsFileModel;
            QString *logsfDir;
            QPushButton *logsRefreshButton;
            void loadLog();


            //Right collumn of logs tab splitter
            QWidget *logsDisplayW;
            QVBoxLayout *logsDisplayVLayout;
            QLabel *logsDisplayLbl;
            QWidget *logsDisplayLowerW;
            QTextBrowser *logsDisplayTextBrowser;
            QVBoxLayout *logsDisplayLowerVLayout;

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
