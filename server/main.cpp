#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8")); //支持中文文件名显示

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);

    w.setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/beijing.jpg")));
    w.setPalette(palette);

    w.show();
    
    return a.exec();
}
