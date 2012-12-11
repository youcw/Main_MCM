/********************************************************************************
** Form generated from reading UI file 'netdialog.ui'
**
** Created: Fri Dec 7 17:17:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETDIALOG_H
#define UI_NETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NetDialog
{
public:
    QPushButton *n;
    QPushButton *netlogbutton;
    QPushButton *netexitbutton;
    QLineEdit *netlineEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *NetDialog)
    {
        if (NetDialog->objectName().isEmpty())
            NetDialog->setObjectName(QString::fromUtf8("NetDialog"));
        NetDialog->resize(400, 300);
        n = new QPushButton(NetDialog);
        n->setObjectName(QString::fromUtf8("n"));
        n->setGeometry(QRect(50, 130, 98, 27));
        netlogbutton = new QPushButton(NetDialog);
        netlogbutton->setObjectName(QString::fromUtf8("netlogbutton"));
        netlogbutton->setGeometry(QRect(60, 220, 98, 27));
        netexitbutton = new QPushButton(NetDialog);
        netexitbutton->setObjectName(QString::fromUtf8("netexitbutton"));
        netexitbutton->setGeometry(QRect(220, 220, 98, 27));
        netlineEdit = new QLineEdit(NetDialog);
        netlineEdit->setObjectName(QString::fromUtf8("netlineEdit"));
        netlineEdit->setGeometry(QRect(170, 130, 161, 27));
        label = new QLabel(NetDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 170, 121, 20));
        label_2 = new QLabel(NetDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 46, 91, 31));
        QFont font;
        font.setPointSize(16);
        label_2->setFont(font);

        retranslateUi(NetDialog);

        QMetaObject::connectSlotsByName(NetDialog);
    } // setupUi

    void retranslateUi(QDialog *NetDialog)
    {
        NetDialog->setWindowTitle(QApplication::translate("NetDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        n->setText(QApplication::translate("NetDialog", "\347\233\256\346\240\207IP", 0, QApplication::UnicodeUTF8));
        netlogbutton->setText(QApplication::translate("NetDialog", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        netexitbutton->setText(QApplication::translate("NetDialog", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NetDialog", "\344\276\213  192.168.1.120", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NetDialog", "\347\275\221\347\273\234\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NetDialog: public Ui_NetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDIALOG_H
