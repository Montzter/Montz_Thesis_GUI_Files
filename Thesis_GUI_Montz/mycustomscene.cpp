#include "mycustomscene.h"
#include "mainwindow.h"

myCustomScene::myCustomScene(QWidget *parent)
{
    tracking = false;
    scaleTracking = false;
    stall = false;
}

void myCustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(stall)
        return;
    emit sceneMousePressed(event->scenePos().x());
    emit scenePosClicked(event->scenePos());
    scaleTracking = true;
}

void myCustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(stall)
        return;

    if(tracking)
    {
        emit scenePosClicked(event->scenePos());
        emit sceneMouseMoved(event->scenePos());
    }

    if(scaleTracking)
        emit sceneMouseReleased(event->scenePos().x());
}

void myCustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(stall)
    {
        stall = false;
        return;
    }
    emit sceneMouseReleased(event->scenePos().x());
    scaleTracking = false;


}

void myCustomScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    tracking = !tracking;
    stall = true;
    emit sceneMouseDoubleClicked();

}
