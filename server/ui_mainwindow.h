/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Fri Dec 7 17:17:28 2012
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *VideoButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *datelabel;
    QLabel *weeklabel;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QPushButton *pushButton;
    QLabel *label_24;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        MainWindow->setWindowTitle(QString::fromUtf8("MainWindow"));
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        VideoButton = new QPushButton(centralWidget);
        VideoButton->setObjectName(QString::fromUtf8("VideoButton"));
        VideoButton->setGeometry(QRect(710, 390, 66, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Sans Serif"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        VideoButton->setFont(font);
        VideoButton->setCursor(QCursor(Qt::ArrowCursor));
        VideoButton->setFocusPolicy(Qt::NoFocus);
        VideoButton->setContextMenuPolicy(Qt::NoContextMenu);
#ifndef QT_NO_STATUSTIP
        VideoButton->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/video.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        VideoButton->setIcon(icon);
        VideoButton->setIconSize(QSize(98, 71));
        VideoButton->setAutoDefault(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(700, 34, 40, 35));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(760, 95, 40, 35));
        QFont font2;
        font2.setPointSize(15);
        label_2->setFont(font2);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(770, 170, 40, 35));
        label_3->setFont(font2);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(750, 250, 40, 35));
        label_4->setFont(font2);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(700, 300, 40, 35));
        label_5->setFont(font2);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(620, 320, 40, 35));
        label_6->setFont(font2);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(540, 300, 40, 35));
        label_7->setFont(font2);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(480, 250, 40, 35));
        label_8->setFont(font2);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(470, 170, 40, 35));
        label_9->setFont(font2);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(470, 91, 40, 35));
        label_10->setFont(font2);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(530, 33, 40, 35));
        label_11->setFont(font2);
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(620, 10, 40, 35));
        label_12->setFont(font2);
        datelabel = new QLabel(centralWidget);
        datelabel->setObjectName(QString::fromUtf8("datelabel"));
        datelabel->setGeometry(QRect(590, 240, 131, 31));
        QFont font3;
        font3.setPointSize(13);
        datelabel->setFont(font3);
        weeklabel = new QLabel(centralWidget);
        weeklabel->setObjectName(QString::fromUtf8("weeklabel"));
        weeklabel->setGeometry(QRect(610, 270, 71, 31));
        weeklabel->setFont(font3);
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(180, 300, 101, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(350, 60, 34, 31));
        QFont font4;
        font4.setPointSize(20);
        label_14->setFont(font4);
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(220, 20, 34, 31));
        label_15->setFont(font4);
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(420, 190, 34, 31));
        label_16->setFont(font4);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(390, 330, 41, 31));
        label_17->setFont(font4);
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(70, 60, 41, 31));
        label_18->setFont(font4);
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(2, 190, 41, 31));
        label_19->setFont(font4);
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 330, 41, 31));
        label_20->setFont(font4);
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(284, 420, 34, 31));
        label_21->setFont(font4);
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(180, 320, 141, 20));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(730, 460, 31, 17));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(570, 390, 66, 71));
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/setting.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(98, 71));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(590, 460, 31, 17));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        VideoButton->setText(QString());
        label->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", " 3", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", " 5", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", " 6", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "  8", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "9", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "11", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "12", 0, QApplication::UnicodeUTF8));
        datelabel->setText(QString());
        weeklabel->setText(QString());
        label_13->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246(\346\221\204\346\260\217\345\272\246)", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "20", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", " 30", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "-10", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "-20", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "-30", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "40", 0, QApplication::UnicodeUTF8));
        label_22->setText(QString());
        label_23->setText(QApplication::translate("MainWindow", "\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        label_24->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
