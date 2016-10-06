/********************************************************************************
** Form generated from reading UI file 'colorkey.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORKEY_H
#define UI_COLORKEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ColorKey
{
public:

    void setupUi(QDialog *ColorKey)
    {
        if (ColorKey->objectName().isEmpty())
            ColorKey->setObjectName(QStringLiteral("ColorKey"));
        ColorKey->resize(227, 232);
        ColorKey->setMinimumSize(QSize(227, 232));
        ColorKey->setMaximumSize(QSize(227, 232));

        retranslateUi(ColorKey);

        QMetaObject::connectSlotsByName(ColorKey);
    } // setupUi

    void retranslateUi(QDialog *ColorKey)
    {
        ColorKey->setWindowTitle(QApplication::translate("ColorKey", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ColorKey: public Ui_ColorKey {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORKEY_H
