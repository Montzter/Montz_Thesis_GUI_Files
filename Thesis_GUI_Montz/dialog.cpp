#include "ui_dialog.h"
#include "dialog.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QSerialPortInfo>
#include <QSerialPort>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //QSerialPortInfo spinfo;
    //int size = spinfo.availablePorts().size();
    /*
    for(int i = 0;i<size;i++)
    {
        //ui->PortComboBox->setCurrentIndex(i);
        ui->PortComboBox->setItemText(i,spinfo.portName());
    }
    ui->PortComboBox->setCurrentIndex(0);
    */

    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        if(!port.isBusy())
            ui->PortComboBox->addItem(port.portName());
    }

    Q_FOREACH(qint32 baudR, QSerialPortInfo::standardBaudRates())
    {
        ui->BaudRateComboBox->addItem(QString::number(baudR));
    }

    ui->DataComboBox->addItem(QString::number(QSerialPort::Data7));
    ui->DataComboBox->addItem(QString::number(QSerialPort::Data8));

    ui->ParityComboBox->addItem("none");
    ui->ParityComboBox->addItem("odd");
    ui->ParityComboBox->addItem("even");
    ui->ParityComboBox->addItem("mark");
    ui->ParityComboBox->addItem("space");

    ui->StopComboBox->addItem("1 bit");
    ui->StopComboBox->addItem("1.5 bit");
    ui->StopComboBox->addItem("2 bit");

    ui->FlowControlComboBox->addItem("Xon/Xoff");
    ui->FlowControlComboBox->addItem("hardware");
    ui->FlowControlComboBox->addItem("none");


    QIcon icon = windowIcon();
    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
    setWindowIcon(icon);

    setModal(true);
    setWindowTitle("Settings");
    show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Show()
{
    show();
}

void Dialog::SaveSettings()
{
    QSettings setting("MontzThesis","GUISettingsFile");
    setting.beginGroup("Dialog");
    setting.setValue("Port",ui->PortComboBox->currentIndex());
    setting.setValue("Baud Rate",ui->BaudRateComboBox->currentIndex());
    setting.setValue("Data",ui->DataComboBox->currentIndex());
    setting.setValue("Parity",ui->ParityComboBox->currentIndex());
    setting.setValue("Stop",ui->StopComboBox->currentIndex());
    setting.setValue("Flow Control",ui->FlowControlComboBox->currentIndex());
    if(ui->SaveLogYes->isChecked())
        setting.setValue("Save Log",true);
    else
        setting.setValue("Save Log",false);
    setting.setValue("Log Save Dir",ui->LogSaveDirLineEdit->text());
    setting.setValue("Image Save Dir",ui->ImageSaveDirLineEdit->text());
    if(ui->SystemMonitorYes->isChecked())
        setting.setValue("System Monitor Mode",true);
    else
        setting.setValue("System Monitor Mode",false);
}

void Dialog::on_SaveButton_clicked()
{
    ☺♣
}
