#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <qmainwindow.h>
#include <QtWidgets>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void SaveSettings();
    void LoadSettings();
    ~Dialog();

public slots:
    void Show();

private slots:
    void on_SaveButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
