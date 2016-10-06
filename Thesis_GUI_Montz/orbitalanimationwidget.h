#ifndef ORBITALANIMATIONWIDGET_H
#define ORBITALANIMATIONWIDGET_H

#include <QWidget>
#include <QtWidgets>

class OrbitalAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OrbitalAnimationWidget(QWidget *parent = 0);


signals:

public slots:
    void startAnimation(int Cycles, int timeToTX, int orbitalPeriod);
    void stopAnimation();
    void resetWidget();
    void timerTimeout();
    void setSatelliteLocation(double angle);
    void initializeText();
    void updateText();

private:
    QVBoxLayout *mainLayout;
    QLabel *cyclesLeftLabel;
    QLabel *timeLeftInCycleLabel;
    QLabel *timeToRXLabel;
    QLabel *timeLeftSimulationLabel;
    QGraphicsView *orbitalView;
    QGraphicsScene *orbitalScene;
    QTimer *mainTimer;
    QElapsedTimer *eTimer;
    QImage *groundStationImage;
    QPixmap *orbitSatImage;
    QGraphicsPixmapItem *bgPixmapItem;
    QGraphicsPixmapItem *gsPixmapItem;
    QGraphicsPixmapItem *osPixmapItem;
    int angleIncrement;
    int numCycles;
    int oPeriod;
    int ttTX;
    void initializeGroundStation();
    void initializeSatellite();
    void setGroundStationLocation(int orbitalPeriod,int timeToTX);

};

#endif // ORBITALANIMATIONWIDGET_H
