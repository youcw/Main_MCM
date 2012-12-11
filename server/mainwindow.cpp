#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(init_device(&fd)==-1)
    {
        printf("open failed\n");
    }

    connect(ui->VideoButton,SIGNAL(clicked()),this,SLOT(buttonfunction()));

    ui->datelabel->setText(QDateTime::currentDateTime().toString("yyyy,MM,dd"));
    ui->weeklabel->setText(QDateTime::currentDateTime().toString("dddd"));

    QTimer *timer=new QTimer(this);
    QTimer *temptimer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(temptimer,SIGNAL(timeout()),this,SLOT(get_ds18b20_temperature()));
    timer->start(1000);
    temptimer->start(1000);

    int arg = 12;
    ioctl(fd,IOCTL_DS18B20_S_BIT,&arg);

}

void MainWindow::get_ds18b20_temperature()
{
    int data;
    read(fd, &data, sizeof(data));

    tempinfo = (double)data / 100;
}

void MainWindow::buttonfunction(void)
{
    QMessageBox::question(this,tr("摄像头"),QString(tr("建设中")));
}

void MainWindow::paintEvent(QPaintEvent *) {
    printclock();
    printtemp();
}

void MainWindow::printclock()
{
     ui->datelabel->setText(QDateTime::currentDateTime().toString("yyyy,MM,dd"));
     ui->weeklabel->setText(QDateTime::currentDateTime().toString("dddd"));

    static const QPoint hourHand[3]={
    QPoint(4,8),QPoint(-4,8),QPoint(0,-40)};
    static const QPoint minuteHand[3]={
    QPoint(4,8),QPoint(-4,8),QPoint(0,-50)};

    QColor hourColor(180,0,180);

    QColor minuteColor(0,180,180);

    int side = qMin(width()/2,height());

    QTime time=QTime::currentTime();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(width()*3/4.0+30,height()/4.0+65);


    painter.scale(side/200.0,side/200.0);

    painter.setPen(Qt::NoPen);

    painter.setBrush(hourColor);

    painter.save();

    painter.eraseRect(0,0,800,480);

    painter.rotate(30.0*(time.hour()+time.minute()/60.0));

    painter.drawConvexPolygon(hourHand,3);

    painter.restore();

    painter.setPen(hourColor);

    for(int i=0;i<12;++i)
    {
         painter.rotate(30.0);

         painter.drawLine(62,0,70,0);
    }

    painter.setPen(Qt::NoPen);

    painter.setBrush(minuteColor);

    painter.save();

    painter.rotate(6.0*(time.minute()+time.second()/60.0));

    painter.drawConvexPolygon(minuteHand,3);

    painter.restore();

    painter.setPen(minuteColor);

    for(int j=0;j<60;j++)
    {
         if((j%5)!=0) {
             painter.drawLine(65,0,70,0);
         }
         painter.rotate(6.0);
    }

}

void MainWindow::printtemp()
{
    char tmp[20];
    sprintf(tmp,"当前温度%.1f℃",tempinfo);
    ui->label_13->setText(tmp);

    static const QPoint tempHand[3]={
    QPoint(4,8),QPoint(-4,8),QPoint(0,-90)};

    QColor tempColdColor(0,180,180);
    QColor tempCoolColor(0,180,0);
    QColor tempHotColor(180,0,0);

    QPainter painter2(this);

    painter2.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width()/2,height());

    painter2.translate(width()/4.0+30,height()/2.0);

    painter2.scale(side/200.0,side/200.0);
    painter2.setPen(Qt::NoPen);
    if( (tempinfo)<18.0) {
        ui->label_22->setText("当前人体感觉寒冷");
        painter2.setBrush(tempColdColor);
    }
    else if( (tempinfo)>=18.0 && (tempinfo)<30.0 ) {
        ui->label_22->setText("当前人体感觉舒适");
        painter2.setBrush(tempCoolColor);
    }
    else if( (tempinfo)>=30.0) {
        ui->label_22->setText("当前人体感觉炎热");
        painter2.setBrush(tempHotColor);
    }
    painter2.save();
    painter2.rotate((tempinfo)*(4.0));

    painter2.drawConvexPolygon(tempHand,3);
    painter2.restore();
    painter2.setPen(tempColdColor);

    for(int k=0;k<90;++k)
    {
        if(k>40 && k<60) {
            painter2.rotate(4.0);
            continue;
        }
        if((k%5)==0) {
            painter2.drawLine(0,-85,0,-95);
        }
        painter2.drawLine(0,-85,0,-90);
        painter2.rotate(4.0);
    }

}

int MainWindow::init_device(int *fd)
{
    *fd = open(TEMP_DEV,O_RDWR);
    if(*fd<=0)
    {
        return -1;
    }
    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

