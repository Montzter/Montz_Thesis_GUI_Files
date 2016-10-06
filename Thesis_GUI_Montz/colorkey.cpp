#include "colorkey.h"
#include "ui_colorkey.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QGraphicsTextItem>
#include <QtCore>
#include <QMoveEvent>

ColorKey::ColorKey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorKey)
{

    ui->setupUi(this);

    dX = 0;
    dY = 0;

    setWindowTitle("Diagram Color Key");

    QGraphicsView *mView = new QGraphicsView;

    mView->setStyleSheet( "QGraphicsView { border-style: none; background-color: \"#F0F0F0\"}" );

    QGraphicsScene *mScene = new QGraphicsScene;
    mView->setScene(mScene);

    QGridLayout *mLayout = new QGridLayout;
    mLayout->addWidget(mView);
    this->setLayout(mLayout);

    //Off
    QLinearGradient *rect1Gradient = new QLinearGradient(0,50,200,70);
    rect1Gradient->setColorAt(0.0,"#DD0000");
    rect1Gradient->setColorAt(1.0,"#990000");
    mScene->addRect(0,50,200,20,QPen(Qt::black),*rect1Gradient);
    QGraphicsTextItem *mText = mScene->addText("Off",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,47);//-50,45);

    //Idle
    QLinearGradient *rect2Gradient = new QLinearGradient(0,110,200,130);
    rect2Gradient->setColorAt(0.0,"#d3d3d3");
    rect2Gradient->setColorAt(1.0,"#545454");
    mScene->addRect(0,110,200,20,QPen(Qt::black),*rect2Gradient);
    mText = mScene->addText("Idle",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,107);//-50,105);

    //On
    QLinearGradient *rect3Gradient = new QLinearGradient(0,80,200,100);
    rect3Gradient->setColorAt(0.0,"#00DD00");
    rect3Gradient->setColorAt(1.0,"#009900");
    mScene->addRect(0,80,200,20,QPen(Qt::black),*rect3Gradient);
    mText = mScene->addText("On",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,77);//-50,75);

    //Warming Up
    QLinearGradient *rect4Gradient = new QLinearGradient(0,140,200,160);
    rect4Gradient->setColorAt(0.0,"#ffc04d");
    rect4Gradient->setColorAt(1.0,"#cc8400");
    mScene->addRect(0,140,200,20,QPen(Qt::black),*rect4Gradient);
    mText = mScene->addText("Warming Up",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,137);//-50,135);

    //Busy
    QLinearGradient *rect5Gradient = new QLinearGradient(0,170,200,190);
    rect5Gradient->setColorAt(0.0,"#7fafdd");
    rect5Gradient->setColorAt(1.0,"#4c6984");
    mScene->addRect(0,170,200,20,QPen(Qt::black),*rect5Gradient);
    mText = mScene->addText("Busy",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,167);//-50,135);

    //FFC
    QLinearGradient *rect6Gradient = new QLinearGradient(0,200,200,230);
    rect6Gradient->setColorAt(0.0,"#3f3f3f");
    rect6Gradient->setColorAt(1.0,"#000000");
    mScene->addRect(0,200,200,20,QPen(Qt::black),*rect6Gradient);
    mText = mScene->addText("FFC",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,197);//-50,135);
    mText->setDefaultTextColor(Qt::white);

    //Capturing Image
    QLinearGradient *rect7Gradient = new QLinearGradient(0,230,200,260);
    rect7Gradient->setColorAt(0.0,"#ffff7f");
    rect7Gradient->setColorAt(1.0,"#ffff7f");
    mScene->addRect(0,230,200,20,QPen(Qt::black),*rect7Gradient);
    mText = mScene->addText("Capturing Image",QFont("Times",12,QFont::Bold,false));
    mText->setPos(0,227);//-50,135);

    QIcon icon = windowIcon();
    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
    setWindowIcon(icon);
}

ColorKey::~ColorKey()
{
    delete ui;
}

void ColorKey::setDistances(int dXin, int dYin)
{
    dX = dXin;
    dY = dYin;
}

void ColorKey::moveEvent(QMoveEvent * event)
{
    QDialog::moveEvent(event);


    qDebug() << (event->type() == event->DragMove);
    setDistances(this->pos().x(),this->pos().y());
}

QPoint ColorKey::getDistances()
{
    return QPoint(dX,dY);
}
