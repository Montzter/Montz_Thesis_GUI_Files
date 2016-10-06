#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <orientationdialog.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //connect(ui->pngcsvToolButton,SIGNAL(clicked(bool)),this,SLOT(on_pngcsvToolButton_clicked()));

    //Setup dialog box
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        if(!port.isBusy())
            ui->PortComboBox->addItem(port.portName());
    }

    Q_FOREACH(qint32 baudR, QSerialPortInfo::standardBaudRates())
    {
        ui->BaudRateComboBox->addItem(QString::number(baudR));
    }
    ui->BaudRateComboBox->addItem(QString::number(460800));

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


    //Load the saved settings and apply to
    QSettings setting("MontzThesis","GUISettingsFile");
    setting.beginGroup("Dialog");
    QVariant Port = setting.value("Port","COM1");
    QVariant BaudRate = setting.value("Baud Rate","115200");
    QVariant Data = setting.value("Data","8 bit");
    QVariant Parity = setting.value("Parity","none");
    QVariant Stop = setting.value("Stop","1 bit");
    QVariant FlowControl = setting.value("Flow Control","none");
    QVariant SaveLog = setting.value("Save Log","true");

    QVariant LogSaveDir = setting.value("Log Save Dir",".\\Logs\\");
    QVariant ImageSaveDir = setting.value("Image Save Dir",".\\Images\\");
    QVariant SaveFileDir = setting.value("PNG CSV Save Dir",".\\Saves\\");

    QVariant SystemMonitorMode = setting.value("System Monitor Mode", "true");

    QVariant SystemAnimationEnabled = setting.value("Simulation Animation Enable", "true");



    setting.endGroup();

    //Setup PortComboBox to saved setting
    for(int h = 0; h < ui->PortComboBox->count(); h++)
    {
        if(!QString::compare(Port.toString(),ui->PortComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->PortComboBox->setCurrentIndex(h);
            break;
        }
    }

    //Setup Baud Rate to saved setting
    for(int h = 0; h < ui->BaudRateComboBox->count(); h++)
    {
        if(!QString::compare(BaudRate.toString(),ui->BaudRateComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->BaudRateComboBox->setCurrentIndex(h);
            break;
        }
    }

    //Setup Data to saved setting
    for(int h = 0; h < ui->DataComboBox->count(); h++)
    {
        if(!QString::compare(Data.toString(),ui->DataComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->DataComboBox->setCurrentIndex(h);
            break;
        }
    }

    //Setup Parity to saved setting
    for(int h = 0; h < ui->ParityComboBox->count(); h++)
    {
        if(!QString::compare(Parity.toString(),ui->ParityComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->ParityComboBox->setCurrentIndex(h);
            break;
        }
    }

    //Setup Stop to saved setting
    for(int h = 0; h < ui->StopComboBox->count(); h++)
    {
        if(!QString::compare(Stop.toString(),ui->StopComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->StopComboBox->setCurrentIndex(h);
            break;
        }
    }

    //Setup Flow Control to saved setting
    for(int h = 0; h < ui->FlowControlComboBox->count(); h++)
    {
        if(!QString::compare(FlowControl.toString(),ui->FlowControlComboBox->itemText(h),Qt::CaseInsensitive))
        {
            ui->FlowControlComboBox->setCurrentIndex(h);
            break;
        }
    }


    //Setup Save Log to saved setting
    if(!QString::compare(SaveLog.toString(),"true",Qt::CaseInsensitive))
        ui->SaveLogYes->setChecked(true);
    else
        ui->SaveLogNo->setChecked(true);


    ui->LogSaveDirLineEdit->setText(LogSaveDir.toString());
    ui->ImageSaveDirLineEdit->setText(ImageSaveDir.toString());
    ui->pngCsvSaveDirectoryLineEdit->setText(SaveFileDir.toString());

    if(!QString::compare(SystemMonitorMode.toString(),"true",Qt::CaseInsensitive))
        ui->SystemMonitorYes->setChecked(true);
    else
        ui->SystemMonitorNo->setChecked(true);


    if(!QString::compare(SystemAnimationEnabled.toString(),"true",Qt::CaseInsensitive))
        ui->simAnimationEnable->setChecked(true);
    else
        ui->simAnimationDisable->setChecked(true);

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
    setting.setValue("Port",ui->PortComboBox->currentText());
    setting.setValue("Baud Rate",ui->BaudRateComboBox->currentText());
    setting.setValue("Data",ui->DataComboBox->currentText());
    setting.setValue("Parity",ui->ParityComboBox->currentText());
    setting.setValue("Stop",ui->StopComboBox->currentText());
    setting.setValue("Flow Control",ui->FlowControlComboBox->currentText());
    if(ui->SaveLogYes->isChecked())
        setting.setValue("Save Log",true);
    else
        setting.setValue("Save Log",false);
    setting.setValue("Log Save Dir",ui->LogSaveDirLineEdit->text());
    setting.setValue("Image Save Dir",ui->ImageSaveDirLineEdit->text());
    setting.setValue("PNG CSV Save Dir",ui->pngCsvSaveDirectoryLineEdit->text());
    if(ui->SystemMonitorYes->isChecked())
        setting.setValue("System Monitor Mode",true);
    else
        setting.setValue("System Monitor Mode",false);

    if(ui->simAnimationEnable->isChecked())
        setting.setValue("Simulation Animation Enable",true);
    else
        setting.setValue("Simulation Animation Enable",false);

    setting.endGroup();

}

void Dialog::on_SaveButton_clicked()
{
    SaveSettings();
    emit saveClicked();
}


void Dialog::on_logToolButton_clicked()
{
    if(!QDir(".\\Logs\\").exists())
        QDir().mkdir(".\\Logs\\");

    QString dir = QFileDialog::getExistingDirectory(this,tr("Select Directory for Logs"),".\\Logs\\",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->LogSaveDirLineEdit->setText(dir);
}

void Dialog::on_imageToolButton_clicked()
{
    if(!QDir(".\\Images\\").exists())
        QDir().mkdir(".\\Images\\");

    QString dir = QFileDialog::getExistingDirectory(this,tr("Select Directory for Logs"),".\\Images\\",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->ImageSaveDirLineEdit->setText(dir);
}

void Dialog::on_pngcsvToolButton_clicked()
{
    if(!QDir(".\\Saves\\").exists())
        QDir().mkdir(".\\Saves\\");

    QString dir = QFileDialog::getExistingDirectory(this,tr("Select Directory for PNG and CSV Saves"),".\\Saves\\",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->pngCsvSaveDirectoryLineEdit->setText(dir);
}

void Dialog::on_orientationButton_clicked()
{
    oriSettings = new OrientationDialog(this);
    oriSettings->setAttribute(Qt::WA_DeleteOnClose);
    oriSettings->exec();
}
