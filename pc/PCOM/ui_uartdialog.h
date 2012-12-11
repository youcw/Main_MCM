/********************************************************************************
** Form generated from reading UI file 'uartdialog.ui'
**
** Created: Fri Dec 7 17:17:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UARTDIALOG_H
#define UI_UARTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UartDialog
{
public:
    QPushButton *pushButton;
    QPushButton *uartlogbutton;
    QPushButton *uartreturnbutton;
    QLabel *label;
    QComboBox *UartComboBox;

    void setupUi(QDialog *UartDialog)
    {
        if (UartDialog->objectName().isEmpty())
            UartDialog->setObjectName(QString::fromUtf8("UartDialog"));
        UartDialog->resize(400, 300);
        pushButton = new QPushButton(UartDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 110, 98, 31));
        uartlogbutton = new QPushButton(UartDialog);
        uartlogbutton->setObjectName(QString::fromUtf8("uartlogbutton"));
        uartlogbutton->setGeometry(QRect(50, 210, 98, 27));
        uartreturnbutton = new QPushButton(UartDialog);
        uartreturnbutton->setObjectName(QString::fromUtf8("uartreturnbutton"));
        uartreturnbutton->setGeometry(QRect(200, 210, 98, 27));
        label = new QLabel(UartDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 30, 91, 51));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        UartComboBox = new QComboBox(UartDialog);
        UartComboBox->setObjectName(QString::fromUtf8("UartComboBox"));
        UartComboBox->setGeometry(QRect(170, 110, 141, 31));

        retranslateUi(UartDialog);

        QMetaObject::connectSlotsByName(UartDialog);
    } // setupUi

    void retranslateUi(QDialog *UartDialog)
    {
        UartDialog->setWindowTitle(QApplication::translate("UartDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("UartDialog", "\344\270\262\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        uartlogbutton->setText(QApplication::translate("UartDialog", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        uartreturnbutton->setText(QApplication::translate("UartDialog", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UartDialog", "\344\270\262\345\217\243\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        UartComboBox->clear();
        UartComboBox->insertItems(0, QStringList()
         << QApplication::translate("UartDialog", "ttyS0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyS1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyS2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyS3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyS4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyS5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UartDialog", "ttyUSB5", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class UartDialog: public Ui_UartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UARTDIALOG_H
