#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialog.h"
#include <QDialog>
#include <QMainWindow>
#include <qmainwindow.h>
#include <QtWidgets>
#include <orientationdialog.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void SaveSettings();
    //void LoadSettings();
    ~Dialog();

signals:
    void saveClicked();

public slots:
    void Show();

private slots:
    void on_SaveButton_clicked();

    void on_logToolButton_clicked();

    void on_imageToolButton_clicked();

    void on_pngcsvToolButton_clicked();

    void on_orientationButton_clicked();

private:
    Ui::Dialog *ui;
    OrientationDialog *oriSettings;
};

#endif // DIALOG_H
