#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "logdialog.h"
#include "uartdialog.h"
#include "netdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示
    LogDialog l;
    l.show();
    return a.exec();
}
