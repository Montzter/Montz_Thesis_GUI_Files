#ifndef ORIENTATIONDIALOG_H
#define ORIENTATIONDIALOG_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class OrientationDialog;
}

class OrientationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrientationDialog(QWidget *parent = 0);
    ~OrientationDialog();

private slots:
    void on_saveButton_clicked();


private:
    Ui::OrientationDialog *ui;
    QDoubleValidator *latValidator;
    QDoubleValidator *lonValidator;
    QDoubleValidator *aziValidator;
    QIntValidator *imgDelayValidator;
};

#endif // ORIENTATIONDIALOG_H
