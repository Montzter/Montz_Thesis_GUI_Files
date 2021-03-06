/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_12;
    QFormLayout *formLayout;
    QLabel *label_5;
    QComboBox *PortComboBox;
    QLabel *label_6;
    QComboBox *BaudRateComboBox;
    QLabel *label_7;
    QComboBox *DataComboBox;
    QLabel *label_8;
    QComboBox *ParityComboBox;
    QLabel *label_9;
    QComboBox *StopComboBox;
    QLabel *label_10;
    QComboBox *FlowControlComboBox;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QPushButton *orientationButton;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *SaveLogYes;
    QRadioButton *SaveLogNo;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLineEdit *LogSaveDirLineEdit;
    QToolButton *logToolButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QLineEdit *ImageSaveDirLineEdit;
    QToolButton *imageToolButton;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QLineEdit *pngCsvSaveDirectoryLineEdit;
    QToolButton *pngcsvToolButton;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QRadioButton *SystemMonitorYes;
    QRadioButton *SystemMonitorNo;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *simAnimationEnable;
    QRadioButton *simAnimationDisable;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *SaveButton;
    QPushButton *CloseButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(355, 637);
        Dialog->setMinimumSize(QSize(355, 631));
        Dialog->setMaximumSize(QSize(355, 637));
        Dialog->setStyleSheet(QLatin1String("QGroupBox\n"
"{\n"
"font-weight: bold;\n"
"text-decoration: underline;\n"
"}"));
        Dialog->setSizeGripEnabled(false);
        verticalLayout_5 = new QVBoxLayout(Dialog);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_4 = new QGroupBox(Dialog);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        PortComboBox = new QComboBox(groupBox_4);
        PortComboBox->setObjectName(QStringLiteral("PortComboBox"));
        PortComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, PortComboBox);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        BaudRateComboBox = new QComboBox(groupBox_4);
        BaudRateComboBox->setObjectName(QStringLiteral("BaudRateComboBox"));
        BaudRateComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(1, QFormLayout::FieldRole, BaudRateComboBox);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        DataComboBox = new QComboBox(groupBox_4);
        DataComboBox->setObjectName(QStringLiteral("DataComboBox"));
        DataComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, DataComboBox);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        ParityComboBox = new QComboBox(groupBox_4);
        ParityComboBox->setObjectName(QStringLiteral("ParityComboBox"));
        ParityComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(3, QFormLayout::FieldRole, ParityComboBox);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_9);

        StopComboBox = new QComboBox(groupBox_4);
        StopComboBox->setObjectName(QStringLiteral("StopComboBox"));
        StopComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(4, QFormLayout::FieldRole, StopComboBox);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_10);

        FlowControlComboBox = new QComboBox(groupBox_4);
        FlowControlComboBox->setObjectName(QStringLiteral("FlowControlComboBox"));
        FlowControlComboBox->setMaximumSize(QSize(1677215, 16777215));

        formLayout->setWidget(5, QFormLayout::FieldRole, FlowControlComboBox);


        horizontalLayout_12->addLayout(formLayout);


        verticalLayout_4->addLayout(horizontalLayout_12);


        verticalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(Dialog);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        orientationButton = new QPushButton(groupBox_5);
        orientationButton->setObjectName(QStringLiteral("orientationButton"));

        verticalLayout->addWidget(orientationButton);


        verticalLayout_5->addWidget(groupBox_5);

        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setWordWrap(false);

        horizontalLayout_9->addWidget(label_4);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        SaveLogYes = new QRadioButton(groupBox_3);
        SaveLogYes->setObjectName(QStringLiteral("SaveLogYes"));
        SaveLogYes->setChecked(true);

        horizontalLayout_8->addWidget(SaveLogYes);

        SaveLogNo = new QRadioButton(groupBox_3);
        SaveLogNo->setObjectName(QStringLiteral("SaveLogNo"));

        horizontalLayout_8->addWidget(SaveLogNo);


        horizontalLayout_9->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setWordWrap(false);

        horizontalLayout_10->addWidget(label_3);

        LogSaveDirLineEdit = new QLineEdit(groupBox_3);
        LogSaveDirLineEdit->setObjectName(QStringLiteral("LogSaveDirLineEdit"));

        horizontalLayout_10->addWidget(LogSaveDirLineEdit);

        logToolButton = new QToolButton(groupBox_3);
        logToolButton->setObjectName(QStringLiteral("logToolButton"));

        horizontalLayout_10->addWidget(logToolButton);


        verticalLayout_3->addLayout(horizontalLayout_10);


        verticalLayout_5->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setWordWrap(false);

        horizontalLayout_11->addWidget(label_2);

        ImageSaveDirLineEdit = new QLineEdit(groupBox_2);
        ImageSaveDirLineEdit->setObjectName(QStringLiteral("ImageSaveDirLineEdit"));

        horizontalLayout_11->addWidget(ImageSaveDirLineEdit);

        imageToolButton = new QToolButton(groupBox_2);
        imageToolButton->setObjectName(QStringLiteral("imageToolButton"));

        horizontalLayout_11->addWidget(imageToolButton);


        verticalLayout_2->addLayout(horizontalLayout_11);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_7 = new QGroupBox(Dialog);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_7);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_5->addWidget(label_12);

        pngCsvSaveDirectoryLineEdit = new QLineEdit(groupBox_7);
        pngCsvSaveDirectoryLineEdit->setObjectName(QStringLiteral("pngCsvSaveDirectoryLineEdit"));

        horizontalLayout_5->addWidget(pngCsvSaveDirectoryLineEdit);

        pngcsvToolButton = new QToolButton(groupBox_7);
        pngcsvToolButton->setObjectName(QStringLiteral("pngcsvToolButton"));

        horizontalLayout_5->addWidget(pngcsvToolButton);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_5->addWidget(groupBox_7);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setWordWrap(false);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        SystemMonitorYes = new QRadioButton(groupBox);
        SystemMonitorYes->setObjectName(QStringLiteral("SystemMonitorYes"));
        SystemMonitorYes->setChecked(true);

        horizontalLayout->addWidget(SystemMonitorYes);

        SystemMonitorNo = new QRadioButton(groupBox);
        SystemMonitorNo->setObjectName(QStringLiteral("SystemMonitorNo"));

        horizontalLayout->addWidget(SystemMonitorNo);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_5->addWidget(groupBox);

        groupBox_6 = new QGroupBox(Dialog);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_4->addWidget(label_11);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        simAnimationEnable = new QRadioButton(groupBox_6);
        simAnimationEnable->setObjectName(QStringLiteral("simAnimationEnable"));
        simAnimationEnable->setChecked(true);

        horizontalLayout_4->addWidget(simAnimationEnable);

        simAnimationDisable = new QRadioButton(groupBox_6);
        simAnimationDisable->setObjectName(QStringLiteral("simAnimationDisable"));

        horizontalLayout_4->addWidget(simAnimationDisable);


        verticalLayout_5->addWidget(groupBox_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        SaveButton = new QPushButton(Dialog);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));

        horizontalLayout_3->addWidget(SaveButton);

        CloseButton = new QPushButton(Dialog);
        CloseButton->setObjectName(QStringLiteral("CloseButton"));

        horizontalLayout_3->addWidget(CloseButton);


        verticalLayout_5->addLayout(horizontalLayout_3);

        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox_4->raise();
        groupBox_5->raise();
        groupBox_6->raise();
        groupBox_7->raise();

        retranslateUi(Dialog);
        QObject::connect(CloseButton, SIGNAL(clicked()), Dialog, SLOT(accept()));

        BaudRateComboBox->setCurrentIndex(-1);
        DataComboBox->setCurrentIndex(-1);
        StopComboBox->setCurrentIndex(-1);
        FlowControlComboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        groupBox_4->setTitle(QApplication::translate("Dialog", "Serial Port Setup", 0));
        label_5->setText(QApplication::translate("Dialog", "Port:                            ", 0));
        label_6->setText(QApplication::translate("Dialog", "Baud Rate:", 0));
        label_7->setText(QApplication::translate("Dialog", "Data:", 0));
        label_8->setText(QApplication::translate("Dialog", "Parity:", 0));
        label_9->setText(QApplication::translate("Dialog", "Stop:", 0));
        label_10->setText(QApplication::translate("Dialog", "Flow Control:", 0));
        groupBox_5->setTitle(QApplication::translate("Dialog", "Process Setup", 0));
        orientationButton->setText(QApplication::translate("Dialog", "Process Variables", 0));
        groupBox_3->setTitle(QApplication::translate("Dialog", "Log File Setup", 0));
        label_4->setText(QApplication::translate("Dialog", "Save Log File?", 0));
        SaveLogYes->setText(QApplication::translate("Dialog", "Yes", 0));
        SaveLogNo->setText(QApplication::translate("Dialog", "No", 0));
        label_3->setText(QApplication::translate("Dialog", "Log Save Directory:    ", 0));
        logToolButton->setText(QApplication::translate("Dialog", "...", 0));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Image Save Directory", 0));
        label_2->setText(QApplication::translate("Dialog", "Image Save Directory:", 0));
        imageToolButton->setText(QApplication::translate("Dialog", "...", 0));
        groupBox_7->setTitle(QApplication::translate("Dialog", "PNG and CSV save Directory", 0));
        label_12->setText(QApplication::translate("Dialog", "PNG and CSV Save Directory:", 0));
        pngcsvToolButton->setText(QApplication::translate("Dialog", "...", 0));
        groupBox->setTitle(QApplication::translate("Dialog", "System Monitor Mode", 0));
        label->setText(QApplication::translate("Dialog", "Use System Monitor Mode?\n"
"(Do not use when testing power consumption)", 0));
        SystemMonitorYes->setText(QApplication::translate("Dialog", "Yes", 0));
        SystemMonitorNo->setText(QApplication::translate("Dialog", "No", 0));
        groupBox_6->setTitle(QApplication::translate("Dialog", "Simulation Animation", 0));
        label_11->setText(QApplication::translate("Dialog", "Enable Simulation Animation?             \n"
"(Uses more system resources)", 0));
        simAnimationEnable->setText(QApplication::translate("Dialog", "Enable", 0));
        simAnimationDisable->setText(QApplication::translate("Dialog", "Disable", 0));
        SaveButton->setText(QApplication::translate("Dialog", "Save", 0));
        CloseButton->setText(QApplication::translate("Dialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
