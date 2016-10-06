#include "orientationdialog.h"
#include "ui_orientationdialog.h"
#include "mainwindow.h"
OrientationDialog::OrientationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrientationDialog)
{
    ui->setupUi(this);
    QSettings setting("MontzThesis","GUISettingsFile");
    setting.beginGroup("Orientation");
    ui->lat1ALineEdit->setText(setting.value("Lat1A","0.0").toString());
    ui->lon1ALineEdit->setText(setting.value("Lon1A","0.0").toString());
    ui->azi1ALineEdit->setText(setting.value("Azi1A","0.0").toString());
    ui->lat1BLineEdit->setText(setting.value("Lat1B","0.0").toString());
    ui->lon1BLineEdit->setText(setting.value("Lon1B","0.0").toString());
    ui->azi1BLineEdit->setText(setting.value("Azi1B","0.0").toString());
    ui->lat2ALineEdit->setText(setting.value("Lat2A","0.0").toString());
    ui->lon2ALineEdit->setText(setting.value("Lon2A","0.0").toString());
    ui->azi2ALineEdit->setText(setting.value("Azi2A","0.0").toString());
    ui->lat2BLineEdit->setText(setting.value("Lat2B","0.0").toString());
    ui->lon2BLineEdit->setText(setting.value("Lon2B","0.0").toString());
    ui->azi2BLineEdit->setText(setting.value("Azi2B","0.0").toString());
    ui->lat3ALineEdit->setText(setting.value("Lat3A","0.0").toString());
    ui->lon3ALineEdit->setText(setting.value("Lon3A","0.0").toString());
    ui->azi3ALineEdit->setText(setting.value("Azi3A","0.0").toString());
    ui->lat3BLineEdit->setText(setting.value("Lat3B","0.0").toString());
    ui->lon3BLineEdit->setText(setting.value("Lon3B","0.0").toString());
    ui->azi3BLineEdit->setText(setting.value("Azi3B","0.0").toString());
    ui->imageSpacingDelayLineEdit->setText(setting.value("Image Spacing Delay", "0").toString());
    setting.endGroup();

    latValidator = new QDoubleValidator(this);
    lonValidator = new QDoubleValidator(this);
    aziValidator = new QDoubleValidator(this);
    imgDelayValidator = new QIntValidator(this);

    latValidator->setNotation(QDoubleValidator::StandardNotation);
    lonValidator->setNotation(QDoubleValidator::StandardNotation);
    aziValidator->setNotation(QDoubleValidator::StandardNotation);

    imgDelayValidator->setRange(0,255);

    latValidator->setDecimals(3);
    lonValidator->setDecimals(3);
    aziValidator->setDecimals(3);

    ui->lat1ALineEdit->setValidator(latValidator);
    ui->lat1BLineEdit->setValidator(latValidator);
    ui->lat2ALineEdit->setValidator(latValidator);
    ui->lat2BLineEdit->setValidator(latValidator);
    ui->lat3ALineEdit->setValidator(latValidator);
    ui->lat3BLineEdit->setValidator(latValidator);

    ui->lon1ALineEdit->setValidator(lonValidator);
    ui->lon1BLineEdit->setValidator(lonValidator);
    ui->lon2ALineEdit->setValidator(lonValidator);
    ui->lon2BLineEdit->setValidator(lonValidator);
    ui->lon3ALineEdit->setValidator(lonValidator);
    ui->lon3BLineEdit->setValidator(lonValidator);

    ui->azi1ALineEdit->setValidator(aziValidator);
    ui->azi1BLineEdit->setValidator(aziValidator);
    ui->azi2ALineEdit->setValidator(aziValidator);
    ui->azi2BLineEdit->setValidator(aziValidator);
    ui->azi3ALineEdit->setValidator(aziValidator);
    ui->azi3BLineEdit->setValidator(aziValidator);

    ui->imageSpacingDelayLineEdit->setValidator(imgDelayValidator);

    setWindowTitle("Orientation Data");

    QIcon icon = windowIcon();
    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
    setWindowIcon(icon);
}

OrientationDialog::~OrientationDialog()
{
    delete ui;
}

void OrientationDialog::on_saveButton_clicked()
{
    QSettings setting("MontzThesis","GUISettingsFile");
    setting.beginGroup("Orientation");
    setting.setValue("Lat1A",ui->lat1ALineEdit->text());
    setting.setValue("Lon1A",ui->lon1ALineEdit->text());
    setting.setValue("Azi1A",ui->azi1ALineEdit->text());

    setting.setValue("Lat1B",ui->lat1BLineEdit->text());
    setting.setValue("Lon1B",ui->lon1BLineEdit->text());
    setting.setValue("Azi1B",ui->azi1BLineEdit->text());

    setting.setValue("Lat2A",ui->lat2ALineEdit->text());
    setting.setValue("Lon2A",ui->lon2ALineEdit->text());
    setting.setValue("Azi2A",ui->azi2ALineEdit->text());

    setting.setValue("Lat2B",ui->lat2BLineEdit->text());
    setting.setValue("Lon2B",ui->lon2BLineEdit->text());
    setting.setValue("Azi2B",ui->azi2BLineEdit->text());

    setting.setValue("Lat3A",ui->lat3ALineEdit->text());
    setting.setValue("Lon3A",ui->lon3ALineEdit->text());
    setting.setValue("Azi3A",ui->azi3ALineEdit->text());

    setting.setValue("Lat3B",ui->lat3BLineEdit->text());
    setting.setValue("Lon3B",ui->lon3BLineEdit->text());
    setting.setValue("Azi3B",ui->azi3BLineEdit->text());

    setting.setValue("Image Spacing Delay",ui->imageSpacingDelayLineEdit->text());

    setting.endGroup();
}
