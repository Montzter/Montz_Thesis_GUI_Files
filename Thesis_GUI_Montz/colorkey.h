#ifndef COLORKEY_H
#define COLORKEY_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class ColorKey;
}

class ColorKey : public QDialog
{
    Q_OBJECT

public:
    explicit ColorKey(QWidget *parent = 0);
    ~ColorKey();
    void setDistances(int dXin, int dYin);
    void moveEvent(QMoveEvent * event);
    QPoint getDistances();

private:
    Ui::ColorKey *ui;
    //Distances from QMainWindow::pos()
    int dX;
    int dY;
};

#endif // COLORKEY_H
