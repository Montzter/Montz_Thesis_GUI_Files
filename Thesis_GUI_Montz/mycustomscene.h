#ifndef MYCUSTOMSCENE_H
#define MYCUSTOMSCENE_H

#include <QGraphicsScene>

class myCustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    myCustomScene(QWidget *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void sceneMousePressed(qreal);
    void sceneMouseReleased(qreal);
    void sceneMouseMoved(QPointF);
    void sceneMouseDoubleClicked();
    void scenePosClicked(QPointF);

public slots:

private:
    bool tracking;
    bool scaleTracking;
    bool stall;
};

#endif // MYCUSTOMSCENE_H
