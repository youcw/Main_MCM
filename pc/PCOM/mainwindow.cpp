#include "mainwindow.h"
#include "ui_mainwindow.h"

/* 关闭设备，不要应用QT4的close*/
extern int close (int __fd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /* 创建主界面*/
    ui->setupUi(this);

    /* 创建socket跟设备进行通信*/
    client_addr.sin_family      = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("192.168.0.105");   //无限制
    client_addr.sin_port        = htons(8000);

    if ((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
        printf("socket error\n");
        exit(-1);
    }
    sin_size = sizeof(struct sockaddr_in);

    /*启动定时器，每隔5S查看设备状态和系统状态*/
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CheckMachineStatFunction()));

    /* 寄存器设置*/
    connect(ui->RegisterSettingButton, SIGNAL(clicked()), this, SLOT(RegisterSettingFunction()));

    /* EEPROM设置*/
    connect(ui->EepromSettingButton, SIGNAL(clicked()), this, SLOT(EepromSettingFunction()));

    /* 发送GPRS短信息*/
    connect(ui->SendMessageButton, SIGNAL(clicked()), this, SLOT(SendGprsMessageFunction()));

    /* 发送ZIGBEE控制命令*/
    connect(ui->SendZigbeeMessageButton, SIGNAL(clicked()), this, SLOT(SendZigbeeMessageFunction()));

    /* 报警器*/
    connect(ui->BeepSettingButton, SIGNAL(clicked()), this, SLOT(BeepSettingFunction()));

    /* LED*/
    connect(ui->LedSettingButton, SIGNAL(clicked()), this, SLOT(LedSettingFunction()));

    /* 硬件自检*/
    connect(ui->HardWareTestSelfCheckButton, SIGNAL(clicked()), this, SLOT(HardWareTestSelfFunction()));

    /* 软件更新*/
    connect(ui->SoftWareUpdateButton, SIGNAL(clicked()), this, SLOT(SoftWareUpdateFunction()));

    /* 启动定时器*/
    timer->start(5000000);
}

MainWindow::~MainWindow()
{
    ::close(client_sockfd); //关闭网络
    delete ui;
}


