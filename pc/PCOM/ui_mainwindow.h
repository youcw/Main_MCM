/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Dec 7 17:17:16 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *RegisterButton;
    QPushButton *RegisterAddrButton;
    QFrame *line;
    QPushButton *RegisterDataButton;
    QCheckBox *RegisterReadCheckBox;
    QCheckBox *RegisterWriteCheckBox;
    QLineEdit *RegisterAddrLineEdit;
    QLineEdit *RegisterDataLineEdit;
    QPushButton *EepromButton;
    QLineEdit *EepromDataLineEdit;
    QPushButton *EepromDataButton;
    QCheckBox *EepromReadCheckBox;
    QLineEdit *EepromAddrLineEdit;
    QPushButton *EepromAddrButton;
    QCheckBox *EepromWriteCheckBox;
    QPushButton *CurrentTemperatureButton;
    QLineEdit *CurrnetTemperatureLineEdit;
    QLineEdit *CurrentVoltageLineEdit;
    QPushButton *CurrentVoltageButton;
    QPushButton *SoftWareUpdateButton;
    QPushButton *DeviceStatButton;
    QPushButton *StatButton;
    QPushButton *SendGprsMessageButton;
    QPushButton *ZigbeeButton;
    QPushButton *TelephoneNumberButton;
    QLineEdit *TelephoneNumberLineEdit;
    QLineEdit *MessageLineEdit;
    QPushButton *MessageButton;
    QPushButton *ZigbeeMessageButton;
    QLineEdit *ZigbeeMessageLineEdit;
    QPushButton *BeepButton;
    QCheckBox *BeepOpenCheckBox;
    QCheckBox *BeepCloseCheckBox;
    QPushButton *LedButton;
    QCheckBox *LedCloseCheckBox;
    QCheckBox *LedOpenCheckBox;
    QLineEdit *LedFlashTimeLineEdit;
    QPushButton *LedFlashTimeButton;
    QPushButton *HardWareTestSelf;
    QLineEdit *HardWareTestSelfLineEdit;
    QLineEdit *CpuFreqLineEdit;
    QPushButton *CpuFreqButton;
    QPushButton *FreeMemButton;
    QLineEdit *FreeMemLineEdit;
    QPushButton *FreeDiskSpaceButton;
    QLineEdit *FreeDiskSpaceLineEdit;
    QFrame *line_2;
    QLabel *menu;
    QFrame *line_3;
    QPushButton *RegisterSettingButton;
    QPushButton *EepromSettingButton;
    QPushButton *SendMessageButton;
    QPushButton *SendZigbeeMessageButton;
    QPushButton *BeepSettingButton;
    QPushButton *LedSettingButton;
    QPushButton *HardWareTestSelfCheckButton;
    QLabel *CurrentTimeLabel;
    QDateTimeEdit *dateTimeEdit;
    QPushButton *TimeSettingButton;
    QPushButton *TimeAdjustButton;
    QPushButton *ReConnectButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(797, 514);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RegisterButton = new QPushButton(centralWidget);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));
        RegisterButton->setGeometry(QRect(10, 140, 91, 27));
        RegisterAddrButton = new QPushButton(centralWidget);
        RegisterAddrButton->setObjectName(QString::fromUtf8("RegisterAddrButton"));
        RegisterAddrButton->setGeometry(QRect(140, 140, 61, 27));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(110, 40, 21, 541));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        RegisterDataButton = new QPushButton(centralWidget);
        RegisterDataButton->setObjectName(QString::fromUtf8("RegisterDataButton"));
        RegisterDataButton->setGeometry(QRect(320, 140, 61, 27));
        RegisterReadCheckBox = new QCheckBox(centralWidget);
        RegisterReadCheckBox->setObjectName(QString::fromUtf8("RegisterReadCheckBox"));
        RegisterReadCheckBox->setGeometry(QRect(520, 140, 51, 31));
        RegisterWriteCheckBox = new QCheckBox(centralWidget);
        RegisterWriteCheckBox->setObjectName(QString::fromUtf8("RegisterWriteCheckBox"));
        RegisterWriteCheckBox->setGeometry(QRect(610, 140, 51, 31));
        RegisterAddrLineEdit = new QLineEdit(centralWidget);
        RegisterAddrLineEdit->setObjectName(QString::fromUtf8("RegisterAddrLineEdit"));
        RegisterAddrLineEdit->setGeometry(QRect(200, 140, 91, 27));
        RegisterDataLineEdit = new QLineEdit(centralWidget);
        RegisterDataLineEdit->setObjectName(QString::fromUtf8("RegisterDataLineEdit"));
        RegisterDataLineEdit->setGeometry(QRect(380, 140, 91, 27));
        EepromButton = new QPushButton(centralWidget);
        EepromButton->setObjectName(QString::fromUtf8("EepromButton"));
        EepromButton->setGeometry(QRect(10, 180, 91, 27));
        EepromDataLineEdit = new QLineEdit(centralWidget);
        EepromDataLineEdit->setObjectName(QString::fromUtf8("EepromDataLineEdit"));
        EepromDataLineEdit->setGeometry(QRect(380, 180, 91, 27));
        EepromDataButton = new QPushButton(centralWidget);
        EepromDataButton->setObjectName(QString::fromUtf8("EepromDataButton"));
        EepromDataButton->setGeometry(QRect(320, 180, 61, 27));
        EepromReadCheckBox = new QCheckBox(centralWidget);
        EepromReadCheckBox->setObjectName(QString::fromUtf8("EepromReadCheckBox"));
        EepromReadCheckBox->setGeometry(QRect(520, 180, 51, 31));
        EepromAddrLineEdit = new QLineEdit(centralWidget);
        EepromAddrLineEdit->setObjectName(QString::fromUtf8("EepromAddrLineEdit"));
        EepromAddrLineEdit->setGeometry(QRect(200, 180, 91, 27));
        EepromAddrButton = new QPushButton(centralWidget);
        EepromAddrButton->setObjectName(QString::fromUtf8("EepromAddrButton"));
        EepromAddrButton->setGeometry(QRect(140, 180, 61, 27));
        EepromWriteCheckBox = new QCheckBox(centralWidget);
        EepromWriteCheckBox->setObjectName(QString::fromUtf8("EepromWriteCheckBox"));
        EepromWriteCheckBox->setGeometry(QRect(610, 180, 51, 31));
        CurrentTemperatureButton = new QPushButton(centralWidget);
        CurrentTemperatureButton->setObjectName(QString::fromUtf8("CurrentTemperatureButton"));
        CurrentTemperatureButton->setGeometry(QRect(320, 60, 71, 27));
        CurrnetTemperatureLineEdit = new QLineEdit(centralWidget);
        CurrnetTemperatureLineEdit->setObjectName(QString::fromUtf8("CurrnetTemperatureLineEdit"));
        CurrnetTemperatureLineEdit->setGeometry(QRect(390, 60, 81, 27));
        CurrentVoltageLineEdit = new QLineEdit(centralWidget);
        CurrentVoltageLineEdit->setObjectName(QString::fromUtf8("CurrentVoltageLineEdit"));
        CurrentVoltageLineEdit->setGeometry(QRect(590, 60, 71, 27));
        CurrentVoltageButton = new QPushButton(centralWidget);
        CurrentVoltageButton->setObjectName(QString::fromUtf8("CurrentVoltageButton"));
        CurrentVoltageButton->setGeometry(QRect(520, 60, 71, 27));
        SoftWareUpdateButton = new QPushButton(centralWidget);
        SoftWareUpdateButton->setObjectName(QString::fromUtf8("SoftWareUpdateButton"));
        SoftWareUpdateButton->setGeometry(QRect(700, 60, 91, 27));
        DeviceStatButton = new QPushButton(centralWidget);
        DeviceStatButton->setObjectName(QString::fromUtf8("DeviceStatButton"));
        DeviceStatButton->setEnabled(true);
        DeviceStatButton->setGeometry(QRect(10, 60, 91, 27));
        StatButton = new QPushButton(centralWidget);
        StatButton->setObjectName(QString::fromUtf8("StatButton"));
        StatButton->setGeometry(QRect(140, 60, 151, 27));
        SendGprsMessageButton = new QPushButton(centralWidget);
        SendGprsMessageButton->setObjectName(QString::fromUtf8("SendGprsMessageButton"));
        SendGprsMessageButton->setGeometry(QRect(10, 220, 91, 27));
        ZigbeeButton = new QPushButton(centralWidget);
        ZigbeeButton->setObjectName(QString::fromUtf8("ZigbeeButton"));
        ZigbeeButton->setGeometry(QRect(10, 260, 91, 27));
        TelephoneNumberButton = new QPushButton(centralWidget);
        TelephoneNumberButton->setObjectName(QString::fromUtf8("TelephoneNumberButton"));
        TelephoneNumberButton->setGeometry(QRect(140, 220, 91, 27));
        TelephoneNumberLineEdit = new QLineEdit(centralWidget);
        TelephoneNumberLineEdit->setObjectName(QString::fromUtf8("TelephoneNumberLineEdit"));
        TelephoneNumberLineEdit->setGeometry(QRect(230, 220, 101, 27));
        MessageLineEdit = new QLineEdit(centralWidget);
        MessageLineEdit->setObjectName(QString::fromUtf8("MessageLineEdit"));
        MessageLineEdit->setGeometry(QRect(450, 220, 211, 27));
        MessageButton = new QPushButton(centralWidget);
        MessageButton->setObjectName(QString::fromUtf8("MessageButton"));
        MessageButton->setGeometry(QRect(360, 220, 91, 27));
        ZigbeeMessageButton = new QPushButton(centralWidget);
        ZigbeeMessageButton->setObjectName(QString::fromUtf8("ZigbeeMessageButton"));
        ZigbeeMessageButton->setGeometry(QRect(140, 260, 91, 27));
        ZigbeeMessageLineEdit = new QLineEdit(centralWidget);
        ZigbeeMessageLineEdit->setObjectName(QString::fromUtf8("ZigbeeMessageLineEdit"));
        ZigbeeMessageLineEdit->setGeometry(QRect(230, 260, 431, 27));
        BeepButton = new QPushButton(centralWidget);
        BeepButton->setObjectName(QString::fromUtf8("BeepButton"));
        BeepButton->setGeometry(QRect(10, 300, 91, 27));
        BeepOpenCheckBox = new QCheckBox(centralWidget);
        BeepOpenCheckBox->setObjectName(QString::fromUtf8("BeepOpenCheckBox"));
        BeepOpenCheckBox->setGeometry(QRect(140, 300, 71, 31));
        BeepCloseCheckBox = new QCheckBox(centralWidget);
        BeepCloseCheckBox->setObjectName(QString::fromUtf8("BeepCloseCheckBox"));
        BeepCloseCheckBox->setGeometry(QRect(270, 300, 71, 31));
        LedButton = new QPushButton(centralWidget);
        LedButton->setObjectName(QString::fromUtf8("LedButton"));
        LedButton->setGeometry(QRect(10, 340, 91, 27));
        LedCloseCheckBox = new QCheckBox(centralWidget);
        LedCloseCheckBox->setObjectName(QString::fromUtf8("LedCloseCheckBox"));
        LedCloseCheckBox->setGeometry(QRect(270, 340, 71, 31));
        LedOpenCheckBox = new QCheckBox(centralWidget);
        LedOpenCheckBox->setObjectName(QString::fromUtf8("LedOpenCheckBox"));
        LedOpenCheckBox->setGeometry(QRect(140, 340, 71, 31));
        LedFlashTimeLineEdit = new QLineEdit(centralWidget);
        LedFlashTimeLineEdit->setObjectName(QString::fromUtf8("LedFlashTimeLineEdit"));
        LedFlashTimeLineEdit->setGeometry(QRect(450, 340, 121, 27));
        LedFlashTimeButton = new QPushButton(centralWidget);
        LedFlashTimeButton->setObjectName(QString::fromUtf8("LedFlashTimeButton"));
        LedFlashTimeButton->setGeometry(QRect(360, 340, 91, 27));
        HardWareTestSelf = new QPushButton(centralWidget);
        HardWareTestSelf->setObjectName(QString::fromUtf8("HardWareTestSelf"));
        HardWareTestSelf->setGeometry(QRect(10, 380, 91, 27));
        HardWareTestSelfLineEdit = new QLineEdit(centralWidget);
        HardWareTestSelfLineEdit->setObjectName(QString::fromUtf8("HardWareTestSelfLineEdit"));
        HardWareTestSelfLineEdit->setGeometry(QRect(140, 380, 521, 27));
        CpuFreqLineEdit = new QLineEdit(centralWidget);
        CpuFreqLineEdit->setObjectName(QString::fromUtf8("CpuFreqLineEdit"));
        CpuFreqLineEdit->setGeometry(QRect(230, 100, 61, 27));
        CpuFreqButton = new QPushButton(centralWidget);
        CpuFreqButton->setObjectName(QString::fromUtf8("CpuFreqButton"));
        CpuFreqButton->setGeometry(QRect(140, 100, 91, 27));
        FreeMemButton = new QPushButton(centralWidget);
        FreeMemButton->setObjectName(QString::fromUtf8("FreeMemButton"));
        FreeMemButton->setGeometry(QRect(320, 100, 71, 27));
        FreeMemLineEdit = new QLineEdit(centralWidget);
        FreeMemLineEdit->setObjectName(QString::fromUtf8("FreeMemLineEdit"));
        FreeMemLineEdit->setGeometry(QRect(390, 100, 81, 27));
        FreeDiskSpaceButton = new QPushButton(centralWidget);
        FreeDiskSpaceButton->setObjectName(QString::fromUtf8("FreeDiskSpaceButton"));
        FreeDiskSpaceButton->setGeometry(QRect(520, 100, 71, 27));
        FreeDiskSpaceLineEdit = new QLineEdit(centralWidget);
        FreeDiskSpaceLineEdit->setObjectName(QString::fromUtf8("FreeDiskSpaceLineEdit"));
        FreeDiskSpaceLineEdit->setGeometry(QRect(590, 100, 71, 27));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 30, 801, 21));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        menu = new QLabel(centralWidget);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setGeometry(QRect(205, -4, 401, 41));
        menu->setFrameShadow(QFrame::Raised);
        menu->setTextFormat(Qt::AutoText);
        menu->setAlignment(Qt::AlignCenter);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(680, 40, 20, 531));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        RegisterSettingButton = new QPushButton(centralWidget);
        RegisterSettingButton->setObjectName(QString::fromUtf8("RegisterSettingButton"));
        RegisterSettingButton->setGeometry(QRect(700, 140, 91, 27));
        EepromSettingButton = new QPushButton(centralWidget);
        EepromSettingButton->setObjectName(QString::fromUtf8("EepromSettingButton"));
        EepromSettingButton->setGeometry(QRect(700, 180, 91, 27));
        SendMessageButton = new QPushButton(centralWidget);
        SendMessageButton->setObjectName(QString::fromUtf8("SendMessageButton"));
        SendMessageButton->setGeometry(QRect(700, 220, 91, 27));
        SendZigbeeMessageButton = new QPushButton(centralWidget);
        SendZigbeeMessageButton->setObjectName(QString::fromUtf8("SendZigbeeMessageButton"));
        SendZigbeeMessageButton->setGeometry(QRect(700, 260, 91, 27));
        BeepSettingButton = new QPushButton(centralWidget);
        BeepSettingButton->setObjectName(QString::fromUtf8("BeepSettingButton"));
        BeepSettingButton->setGeometry(QRect(700, 300, 91, 27));
        LedSettingButton = new QPushButton(centralWidget);
        LedSettingButton->setObjectName(QString::fromUtf8("LedSettingButton"));
        LedSettingButton->setGeometry(QRect(700, 340, 91, 27));
        HardWareTestSelfCheckButton = new QPushButton(centralWidget);
        HardWareTestSelfCheckButton->setObjectName(QString::fromUtf8("HardWareTestSelfCheckButton"));
        HardWareTestSelfCheckButton->setGeometry(QRect(700, 380, 91, 27));
        CurrentTimeLabel = new QLabel(centralWidget);
        CurrentTimeLabel->setObjectName(QString::fromUtf8("CurrentTimeLabel"));
        CurrentTimeLabel->setGeometry(QRect(650, 10, 141, 31));
        dateTimeEdit = new QDateTimeEdit(centralWidget);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(140, 420, 194, 27));
        TimeSettingButton = new QPushButton(centralWidget);
        TimeSettingButton->setObjectName(QString::fromUtf8("TimeSettingButton"));
        TimeSettingButton->setGeometry(QRect(10, 420, 91, 27));
        TimeAdjustButton = new QPushButton(centralWidget);
        TimeAdjustButton->setObjectName(QString::fromUtf8("TimeAdjustButton"));
        TimeAdjustButton->setGeometry(QRect(700, 420, 91, 27));
        ReConnectButton = new QPushButton(centralWidget);
        ReConnectButton->setObjectName(QString::fromUtf8("ReConnectButton"));
        ReConnectButton->setGeometry(QRect(700, 470, 98, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\256\276\345\244\207\346\223\215\344\275\234\344\270\216\347\273\264\346\212\244\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        RegisterButton->setText(QApplication::translate("MainWindow", "\345\257\204\345\255\230\345\231\250:", 0, QApplication::UnicodeUTF8));
        RegisterAddrButton->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        RegisterDataButton->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256:", 0, QApplication::UnicodeUTF8));
        RegisterReadCheckBox->setText(QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8));
        RegisterWriteCheckBox->setText(QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8));
        RegisterAddrLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        RegisterDataLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        EepromButton->setText(QApplication::translate("MainWindow", "EEPROM:", 0, QApplication::UnicodeUTF8));
        EepromDataLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        EepromDataButton->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256:", 0, QApplication::UnicodeUTF8));
        EepromReadCheckBox->setText(QApplication::translate("MainWindow", "\350\257\273", 0, QApplication::UnicodeUTF8));
        EepromAddrLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        EepromAddrButton->setText(QApplication::translate("MainWindow", "\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        EepromWriteCheckBox->setText(QApplication::translate("MainWindow", "\345\206\231", 0, QApplication::UnicodeUTF8));
        CurrentTemperatureButton->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\346\270\251\345\272\246:", 0, QApplication::UnicodeUTF8));
        CurrnetTemperatureLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        CurrentVoltageLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        CurrentVoltageButton->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\347\224\265\345\216\213:", 0, QApplication::UnicodeUTF8));
        SoftWareUpdateButton->setText(QApplication::translate("MainWindow", "\350\275\257\344\273\266\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
        DeviceStatButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        StatButton->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242\344\270\255...", 0, QApplication::UnicodeUTF8));
        SendGprsMessageButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\347\237\255\344\277\241:", 0, QApplication::UnicodeUTF8));
        ZigbeeButton->setText(QApplication::translate("MainWindow", "zigbee:", 0, QApplication::UnicodeUTF8));
        TelephoneNumberButton->setText(QApplication::translate("MainWindow", "\346\211\213\346\234\272\345\217\267:", 0, QApplication::UnicodeUTF8));
        TelephoneNumberLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        MessageLineEdit->setText(QString());
        MessageButton->setText(QApplication::translate("MainWindow", "\344\277\241\346\201\257:", 0, QApplication::UnicodeUTF8));
        ZigbeeMessageButton->setText(QApplication::translate("MainWindow", "\344\277\241\346\201\257:", 0, QApplication::UnicodeUTF8));
        ZigbeeMessageLineEdit->setText(QString());
        BeepButton->setText(QApplication::translate("MainWindow", "\346\212\245\350\255\246\345\231\250:", 0, QApplication::UnicodeUTF8));
        BeepOpenCheckBox->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        BeepCloseCheckBox->setText(QApplication::translate("MainWindow", " \345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        LedButton->setText(QApplication::translate("MainWindow", "LED:", 0, QApplication::UnicodeUTF8));
        LedCloseCheckBox->setText(QApplication::translate("MainWindow", " \345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        LedOpenCheckBox->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        LedFlashTimeLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        LedFlashTimeButton->setText(QApplication::translate("MainWindow", "\351\227\252\347\203\201\345\221\250\346\234\237:", 0, QApplication::UnicodeUTF8));
        HardWareTestSelf->setText(QApplication::translate("MainWindow", "\350\256\276\345\244\207\350\207\252\346\243\200:", 0, QApplication::UnicodeUTF8));
        HardWareTestSelfLineEdit->setText(QString());
        CpuFreqLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        CpuFreqButton->setText(QApplication::translate("MainWindow", "cpu\351\242\221\347\216\207:", 0, QApplication::UnicodeUTF8));
        FreeMemButton->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\345\206\205\345\255\230:", 0, QApplication::UnicodeUTF8));
        FreeMemLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        FreeDiskSpaceButton->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\347\251\272\351\227\264:", 0, QApplication::UnicodeUTF8));
        FreeDiskSpaceLineEdit->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        menu->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">\350\256\276\345\244\207\346\223\215\344\275\234\344\270\216\347\273\264\346\212\244\350\275\257\344\273\266</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        RegisterSettingButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        EepromSettingButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        SendMessageButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        SendZigbeeMessageButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        BeepSettingButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        LedSettingButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        HardWareTestSelfCheckButton->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        CurrentTimeLabel->setText(QApplication::translate("MainWindow", "2012.09.16 12:12:12", 0, QApplication::UnicodeUTF8));
        dateTimeEdit->setDisplayFormat(QApplication::translate("MainWindow", "yyyy-MM-dd hh:mm:ss", 0, QApplication::UnicodeUTF8));
        TimeSettingButton->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264\346\240\241\345\207\206:", 0, QApplication::UnicodeUTF8));
        TimeAdjustButton->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232", 0, QApplication::UnicodeUTF8));
        ReConnectButton->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
