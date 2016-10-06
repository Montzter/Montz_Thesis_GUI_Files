#include "orbitalanimationwidget.h"

OrbitalAnimationWidget::OrbitalAnimationWidget(QWidget *parent) : QWidget(parent)
{   
    mainLayout = new QVBoxLayout;
    cyclesLeftLabel = new QLabel("Cycles left: N/A",this);
    timeLeftInCycleLabel= new QLabel("Time left in cycle: N/A",this);
    timeToRXLabel= new QLabel("Time till tx: N/A",this);
    timeLeftSimulationLabel= new QLabel("Time till process: N/A",this);

    orbitalScene = new QGraphicsScene(this);
    orbitalView = new QGraphicsView(orbitalScene,this);

    mainTimer = new QTimer();
    mainTimer->setSingleShot(true);
    mainTimer->setTimerType(Qt::PreciseTimer);
    eTimer = new QElapsedTimer();
    eTimer->start();

    angleIncrement = 1;

    orbitalView->setRenderHint(QPainter::Antialiasing);
    orbitalView->setMinimumWidth(210);
    orbitalView->setMinimumHeight(210);
    orbitalView->setMaximumWidth(210);
    orbitalView->setMaximumHeight(210);
    //***
    orbitalView->setStyleSheet( "QGraphicsView { border-style: none; }" );
    //***
    initializeGroundStation();
    initializeSatellite();
    initializeText();

    orbitalScene->setSceneRect(0,0,200,200);

    mainLayout->addWidget(orbitalView);
    mainLayout->addWidget(cyclesLeftLabel);
    mainLayout->addWidget(timeLeftInCycleLabel);
    mainLayout->addWidget(timeToRXLabel);
    mainLayout->addWidget(timeLeftSimulationLabel);

    setLayout(mainLayout);

    //**************
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(timerTimeout()));
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(updateText()));
    //**************

    orbitalView->setBackgroundBrush(QImage(":/myFiles/EarthOrbitWVolc.png"));
    orbitalView->setCacheMode(QGraphicsView::CacheBackground);

}

void OrbitalAnimationWidget::initializeGroundStation()
{
    //groundStationImage = new QImage(".\\satTiny.png");
    groundStationImage = new QImage(":/myFiles/satTiny.png");
    gsPixmapItem = new QGraphicsPixmapItem;
    gsPixmapItem = orbitalScene->addPixmap(QPixmap::fromImage(*groundStationImage));
    gsPixmapItem->setOffset(91,12);
    gsPixmapItem->setTransformOriginPoint(100,100);
    setGroundStationLocation(2,1);
}

void OrbitalAnimationWidget::initializeSatellite()
{
    //orbitSatImage = new QPixmap(".\\cubesatTiny.png");
    orbitSatImage = new QPixmap(":/myFiles/cubesatTiny.png");
    osPixmapItem = new QGraphicsPixmapItem;
    osPixmapItem = orbitalScene->addPixmap(*orbitSatImage);
    osPixmapItem->setOffset(91,0);
    osPixmapItem->setTransformOriginPoint(100,100);
    //orbitAngle = 0;
    setSatelliteLocation(0);
}

void OrbitalAnimationWidget::resetWidget()
{
    setGroundStationLocation(2,1);
    setSatelliteLocation(0);
    initializeText();
}

void OrbitalAnimationWidget::setGroundStationLocation(int orbitalPeriod,int timeToTX)
{
    double fraction = (double)timeToTX/(double)orbitalPeriod;
    gsPixmapItem->setRotation(360.0*fraction);
}

void OrbitalAnimationWidget::timerTimeout()
{
    if(eTimer->hasExpired(oPeriod))
    {
        eTimer->restart();
        numCycles -= 1;
    }

    if(numCycles <= 0)
        return;
    else
    {
        mainTimer->start();
        double angleFraction = (eTimer->elapsed() % oPeriod) / (double)oPeriod;
        setSatelliteLocation(angleFraction * 360.0);
    }
}

void OrbitalAnimationWidget::setSatelliteLocation(double angle)
{
    osPixmapItem->setRotation(angle);
}

void OrbitalAnimationWidget::startAnimation(int Cycles,int timeToTX,int orbitalPeriod)
{
    numCycles = Cycles;
    oPeriod = orbitalPeriod * 1000;
    ttTX = timeToTX * 1000;

    setGroundStationLocation(orbitalPeriod,timeToTX);
    setSatelliteLocation(0);
    mainTimer->setInterval((angleIncrement * orbitalPeriod *1000)/(360));
    mainTimer->start();
    eTimer->restart();
    updateText();
}

void OrbitalAnimationWidget::stopAnimation()
{
    mainTimer->stop();
    eTimer->restart();
    resetWidget();
}

void OrbitalAnimationWidget::updateText()
{
    QString tmp;
    tmp = "Cycles left(inclusive): ";
    tmp.append(QString::number(numCycles));
    cyclesLeftLabel->setText(tmp);
    tmp = "Time left in cycle: ";
    tmp.append(QString::number((oPeriod - eTimer->elapsed())/1000.00,'f',2));
    timeLeftInCycleLabel->setText(tmp);

    tmp = "Time till tx: ";
    if(eTimer->elapsed() > ttTX)
        tmp.append("Next orbit");
    else
        tmp.append(QString::number((ttTX - eTimer->elapsed())/1000.00,'f',2));
    timeToRXLabel->setText(tmp);
    tmp = "Time left in simulation: ";
    tmp.append(QString::number(((numCycles - 1) * oPeriod + (oPeriod - eTimer->elapsed()))/1000.00,'f',2));
    timeLeftSimulationLabel->setText(tmp);
}

void OrbitalAnimationWidget::initializeText()
{
    cyclesLeftLabel->setText("Cycles left (inclusive): N/A");
    timeLeftInCycleLabel->setText("Time left in cycle: N/A");
    timeToRXLabel->setText("Time till tx: N/A");
    timeLeftSimulationLabel->setText("Time left in simulation: N/A");
}
