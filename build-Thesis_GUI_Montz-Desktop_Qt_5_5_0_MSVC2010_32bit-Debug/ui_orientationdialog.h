/********************************************************************************
** Form generated from reading UI file 'orientationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORIENTATIONDIALOG_H
#define UI_ORIENTATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OrientationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *orientationGBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *i1AGBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lat1ALineEdit;
    QLabel *label_2;
    QLineEdit *lon1ALineEdit;
    QLabel *label_3;
    QLineEdit *azi1ALineEdit;
    QGroupBox *i1BGBox;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QLineEdit *lat1BLineEdit;
    QLabel *label_5;
    QLineEdit *lon1BLineEdit;
    QLabel *label_6;
    QLineEdit *azi1BLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *i2AGBox;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QLineEdit *lat2ALineEdit;
    QLabel *label_8;
    QLineEdit *lon2ALineEdit;
    QLabel *label_9;
    QLineEdit *azi2ALineEdit;
    QGroupBox *i2BGBox;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLineEdit *lat2BLineEdit;
    QLabel *label_11;
    QLineEdit *lon2BLineEdit;
    QLabel *label_12;
    QLineEdit *azi2BLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *i3AGBox;
    QFormLayout *formLayout_5;
    QLabel *label_13;
    QLineEdit *lat3ALineEdit;
    QLabel *label_14;
    QLineEdit *lon3ALineEdit;
    QLabel *label_15;
    QLineEdit *azi3ALineEdit;
    QGroupBox *i3BGBox;
    QFormLayout *formLayout_6;
    QLabel *label_16;
    QLineEdit *lat3BLineEdit;
    QLabel *label_17;
    QLineEdit *lon3BLineEdit;
    QLabel *label_18;
    QLineEdit *azi3BLineEdit;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_19;
    QLineEdit *imageSpacingDelayLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveButton;
    QPushButton *closeButton;

    void setupUi(QDialog *OrientationDialog)
    {
        if (OrientationDialog->objectName().isEmpty())
            OrientationDialog->setObjectName(QStringLiteral("OrientationDialog"));
        OrientationDialog->resize(308, 474);
        verticalLayout = new QVBoxLayout(OrientationDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        orientationGBox = new QGroupBox(OrientationDialog);
        orientationGBox->setObjectName(QStringLiteral("orientationGBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(orientationGBox->sizePolicy().hasHeightForWidth());
        orientationGBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        orientationGBox->setFont(font);
        verticalLayout_2 = new QVBoxLayout(orientationGBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        i1AGBox = new QGroupBox(orientationGBox);
        i1AGBox->setObjectName(QStringLiteral("i1AGBox"));
        formLayout = new QFormLayout(i1AGBox);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(i1AGBox);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lat1ALineEdit = new QLineEdit(i1AGBox);
        lat1ALineEdit->setObjectName(QStringLiteral("lat1ALineEdit"));
        lat1ALineEdit->setFont(font1);
        lat1ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lat1ALineEdit->setStyleSheet(QStringLiteral(""));
        lat1ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, lat1ALineEdit);

        label_2 = new QLabel(i1AGBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lon1ALineEdit = new QLineEdit(i1AGBox);
        lon1ALineEdit->setObjectName(QStringLiteral("lon1ALineEdit"));
        lon1ALineEdit->setFont(font1);
        lon1ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lon1ALineEdit->setStyleSheet(QStringLiteral(""));
        lon1ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, lon1ALineEdit);

        label_3 = new QLabel(i1AGBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        azi1ALineEdit = new QLineEdit(i1AGBox);
        azi1ALineEdit->setObjectName(QStringLiteral("azi1ALineEdit"));
        azi1ALineEdit->setFont(font1);
        azi1ALineEdit->setLayoutDirection(Qt::LeftToRight);
        azi1ALineEdit->setStyleSheet(QStringLiteral(""));
        azi1ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::FieldRole, azi1ALineEdit);


        horizontalLayout_2->addWidget(i1AGBox);

        i1BGBox = new QGroupBox(orientationGBox);
        i1BGBox->setObjectName(QStringLiteral("i1BGBox"));
        formLayout_2 = new QFormLayout(i1BGBox);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_4 = new QLabel(i1BGBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        lat1BLineEdit = new QLineEdit(i1BGBox);
        lat1BLineEdit->setObjectName(QStringLiteral("lat1BLineEdit"));
        lat1BLineEdit->setFont(font1);
        lat1BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lat1BLineEdit->setStyleSheet(QStringLiteral(""));
        lat1BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lat1BLineEdit);

        label_5 = new QLabel(i1BGBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        lon1BLineEdit = new QLineEdit(i1BGBox);
        lon1BLineEdit->setObjectName(QStringLiteral("lon1BLineEdit"));
        lon1BLineEdit->setFont(font1);
        lon1BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lon1BLineEdit->setStyleSheet(QStringLiteral(""));
        lon1BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lon1BLineEdit);

        label_6 = new QLabel(i1BGBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_6);

        azi1BLineEdit = new QLineEdit(i1BGBox);
        azi1BLineEdit->setObjectName(QStringLiteral("azi1BLineEdit"));
        azi1BLineEdit->setFont(font1);
        azi1BLineEdit->setLayoutDirection(Qt::LeftToRight);
        azi1BLineEdit->setStyleSheet(QStringLiteral(""));
        azi1BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, azi1BLineEdit);


        horizontalLayout_2->addWidget(i1BGBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        i2AGBox = new QGroupBox(orientationGBox);
        i2AGBox->setObjectName(QStringLiteral("i2AGBox"));
        formLayout_3 = new QFormLayout(i2AGBox);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_7 = new QLabel(i2AGBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        lat2ALineEdit = new QLineEdit(i2AGBox);
        lat2ALineEdit->setObjectName(QStringLiteral("lat2ALineEdit"));
        lat2ALineEdit->setFont(font1);
        lat2ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lat2ALineEdit->setStyleSheet(QStringLiteral(""));
        lat2ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lat2ALineEdit);

        label_8 = new QLabel(i2AGBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font1);

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        lon2ALineEdit = new QLineEdit(i2AGBox);
        lon2ALineEdit->setObjectName(QStringLiteral("lon2ALineEdit"));
        lon2ALineEdit->setFont(font1);
        lon2ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lon2ALineEdit->setStyleSheet(QStringLiteral(""));
        lon2ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lon2ALineEdit);

        label_9 = new QLabel(i2AGBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        azi2ALineEdit = new QLineEdit(i2AGBox);
        azi2ALineEdit->setObjectName(QStringLiteral("azi2ALineEdit"));
        azi2ALineEdit->setFont(font1);
        azi2ALineEdit->setLayoutDirection(Qt::LeftToRight);
        azi2ALineEdit->setStyleSheet(QStringLiteral(""));
        azi2ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, azi2ALineEdit);


        horizontalLayout_3->addWidget(i2AGBox);

        i2BGBox = new QGroupBox(orientationGBox);
        i2BGBox->setObjectName(QStringLiteral("i2BGBox"));
        formLayout_4 = new QFormLayout(i2BGBox);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_10 = new QLabel(i2BGBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font1);

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);

        lat2BLineEdit = new QLineEdit(i2BGBox);
        lat2BLineEdit->setObjectName(QStringLiteral("lat2BLineEdit"));
        lat2BLineEdit->setFont(font1);
        lat2BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lat2BLineEdit->setStyleSheet(QStringLiteral(""));
        lat2BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, lat2BLineEdit);

        label_11 = new QLabel(i2BGBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font1);

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_11);

        lon2BLineEdit = new QLineEdit(i2BGBox);
        lon2BLineEdit->setObjectName(QStringLiteral("lon2BLineEdit"));
        lon2BLineEdit->setFont(font1);
        lon2BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lon2BLineEdit->setStyleSheet(QStringLiteral(""));
        lon2BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, lon2BLineEdit);

        label_12 = new QLabel(i2BGBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font1);

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_12);

        azi2BLineEdit = new QLineEdit(i2BGBox);
        azi2BLineEdit->setObjectName(QStringLiteral("azi2BLineEdit"));
        azi2BLineEdit->setFont(font1);
        azi2BLineEdit->setLayoutDirection(Qt::LeftToRight);
        azi2BLineEdit->setStyleSheet(QStringLiteral(""));
        azi2BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, azi2BLineEdit);


        horizontalLayout_3->addWidget(i2BGBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        i3AGBox = new QGroupBox(orientationGBox);
        i3AGBox->setObjectName(QStringLiteral("i3AGBox"));
        formLayout_5 = new QFormLayout(i3AGBox);
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        label_13 = new QLabel(i3AGBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font1);

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_13);

        lat3ALineEdit = new QLineEdit(i3AGBox);
        lat3ALineEdit->setObjectName(QStringLiteral("lat3ALineEdit"));
        lat3ALineEdit->setFont(font1);
        lat3ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lat3ALineEdit->setStyleSheet(QStringLiteral(""));
        lat3ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, lat3ALineEdit);

        label_14 = new QLabel(i3AGBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font1);

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_14);

        lon3ALineEdit = new QLineEdit(i3AGBox);
        lon3ALineEdit->setObjectName(QStringLiteral("lon3ALineEdit"));
        lon3ALineEdit->setFont(font1);
        lon3ALineEdit->setLayoutDirection(Qt::LeftToRight);
        lon3ALineEdit->setStyleSheet(QStringLiteral(""));
        lon3ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, lon3ALineEdit);

        label_15 = new QLabel(i3AGBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font1);

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_15);

        azi3ALineEdit = new QLineEdit(i3AGBox);
        azi3ALineEdit->setObjectName(QStringLiteral("azi3ALineEdit"));
        azi3ALineEdit->setFont(font1);
        azi3ALineEdit->setLayoutDirection(Qt::LeftToRight);
        azi3ALineEdit->setStyleSheet(QStringLiteral(""));
        azi3ALineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, azi3ALineEdit);


        horizontalLayout_4->addWidget(i3AGBox);

        i3BGBox = new QGroupBox(orientationGBox);
        i3BGBox->setObjectName(QStringLiteral("i3BGBox"));
        formLayout_6 = new QFormLayout(i3BGBox);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        label_16 = new QLabel(i3BGBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setFont(font1);

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_16);

        lat3BLineEdit = new QLineEdit(i3BGBox);
        lat3BLineEdit->setObjectName(QStringLiteral("lat3BLineEdit"));
        lat3BLineEdit->setFont(font1);
        lat3BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lat3BLineEdit->setStyleSheet(QStringLiteral(""));
        lat3BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(0, QFormLayout::FieldRole, lat3BLineEdit);

        label_17 = new QLabel(i3BGBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setFont(font1);

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_17);

        lon3BLineEdit = new QLineEdit(i3BGBox);
        lon3BLineEdit->setObjectName(QStringLiteral("lon3BLineEdit"));
        lon3BLineEdit->setFont(font1);
        lon3BLineEdit->setLayoutDirection(Qt::LeftToRight);
        lon3BLineEdit->setStyleSheet(QStringLiteral(""));
        lon3BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(1, QFormLayout::FieldRole, lon3BLineEdit);

        label_18 = new QLabel(i3BGBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setFont(font1);

        formLayout_6->setWidget(2, QFormLayout::LabelRole, label_18);

        azi3BLineEdit = new QLineEdit(i3BGBox);
        azi3BLineEdit->setObjectName(QStringLiteral("azi3BLineEdit"));
        azi3BLineEdit->setFont(font1);
        azi3BLineEdit->setLayoutDirection(Qt::LeftToRight);
        azi3BLineEdit->setStyleSheet(QStringLiteral(""));
        azi3BLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_6->setWidget(2, QFormLayout::FieldRole, azi3BLineEdit);


        horizontalLayout_4->addWidget(i3BGBox);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout->addWidget(orientationGBox);

        groupBox = new QGroupBox(OrientationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font);
        horizontalLayout_5 = new QHBoxLayout(groupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setFont(font1);

        horizontalLayout_5->addWidget(label_19);

        imageSpacingDelayLineEdit = new QLineEdit(groupBox);
        imageSpacingDelayLineEdit->setObjectName(QStringLiteral("imageSpacingDelayLineEdit"));
        imageSpacingDelayLineEdit->setFont(font1);
        imageSpacingDelayLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(imageSpacingDelayLineEdit);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        saveButton = new QPushButton(OrientationDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout->addWidget(saveButton);

        closeButton = new QPushButton(OrientationDialog);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OrientationDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), OrientationDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(OrientationDialog);
    } // setupUi

    void retranslateUi(QDialog *OrientationDialog)
    {
        OrientationDialog->setWindowTitle(QApplication::translate("OrientationDialog", "Dialog", 0));
        orientationGBox->setTitle(QApplication::translate("OrientationDialog", "Orientation Data", 0));
        i1AGBox->setTitle(QApplication::translate("OrientationDialog", "Image 1, Filter A", 0));
        label->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat1ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_2->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon1ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_3->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi1ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        i1BGBox->setTitle(QApplication::translate("OrientationDialog", "Image 1, Filter B", 0));
        label_4->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat1BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_5->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon1BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_6->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi1BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        i2AGBox->setTitle(QApplication::translate("OrientationDialog", "Image 2, Filter A", 0));
        label_7->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat2ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_8->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon2ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_9->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi2ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        i2BGBox->setTitle(QApplication::translate("OrientationDialog", "Image 2, Filter B", 0));
        label_10->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat2BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_11->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon2BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_12->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi2BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        i3AGBox->setTitle(QApplication::translate("OrientationDialog", "Image 3, Filter A", 0));
        label_13->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat3ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_14->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon3ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_15->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi3ALineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        i3BGBox->setTitle(QApplication::translate("OrientationDialog", "Image 3, Filter B", 0));
        label_16->setText(QApplication::translate("OrientationDialog", "Latitude:", 0));
        lat3BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_17->setText(QApplication::translate("OrientationDialog", "Longitude:", 0));
        lon3BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        label_18->setText(QApplication::translate("OrientationDialog", "Azimuth:", 0));
        azi3BLineEdit->setText(QApplication::translate("OrientationDialog", "0.0", 0));
        groupBox->setTitle(QApplication::translate("OrientationDialog", "Image Spacing Delay", 0));
        label_19->setText(QApplication::translate("OrientationDialog", "Image Spacing Delay (sec):", 0));
        imageSpacingDelayLineEdit->setText(QApplication::translate("OrientationDialog", "0", 0));
        saveButton->setText(QApplication::translate("OrientationDialog", "Save", 0));
        closeButton->setText(QApplication::translate("OrientationDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class OrientationDialog: public Ui_OrientationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORIENTATIONDIALOG_H
