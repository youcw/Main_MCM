/********************************************************************************
** Form generated from reading UI file 'logdialog.ui'
**
** Created: Fri Dec 7 17:17:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGDIALOG_H
#define UI_LOGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LogDialog
{
public:
    QPushButton *netbutton;
    QPushButton *uartbutton;
    QLabel *loglabel;

    void setupUi(QDialog *LogDialog)
    {
        if (LogDialog->objectName().isEmpty())
            LogDialog->setObjectName(QString::fromUtf8("LogDialog"));
        LogDialog->resize(381, 255);
        netbutton = new QPushButton(LogDialog);
        netbutton->setObjectName(QString::fromUtf8("netbutton"));
        netbutton->setGeometry(QRect(200, 120, 151, 51));
        uartbutton = new QPushButton(LogDialog);
        uartbutton->setObjectName(QString::fromUtf8("uartbutton"));
        uartbutton->setGeometry(QRect(30, 120, 151, 51));
        loglabel = new QLabel(LogDialog);
        loglabel->setObjectName(QString::fromUtf8("loglabel"));
        loglabel->setGeometry(QRect(110, 40, 151, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        loglabel->setFont(font);

        retranslateUi(LogDialog);

        QMetaObject::connectSlotsByName(LogDialog);
    } // setupUi

    void retranslateUi(QDialog *LogDialog)
    {
        LogDialog->setWindowTitle(QApplication::translate("LogDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        netbutton->setText(QApplication::translate("LogDialog", "\351\200\232\350\277\207\347\275\221\347\273\234\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        uartbutton->setText(QApplication::translate("LogDialog", "\351\200\232\350\277\207\344\270\262\345\217\243\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        loglabel->setText(QApplication::translate("LogDialog", "\351\200\211\346\213\251\347\231\273\345\275\225\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogDialog: public Ui_LogDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGDIALOG_H
