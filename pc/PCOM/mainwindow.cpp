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
}

void MainWindow::init()
{
    if(TransFlag==TRANSFER_UART)
    {
    /* 串口初始化*/
        init_uart();
    }
    else if(TransFlag==TRANSFER_NET)
    {
    uartfd  = 0;
    /* 设置超时时间*/
    //struct timeval time_out;
    //time_out.tv_sec = 5;
    //time_out.tv_usec = 0;       //设置超时时间10秒

    /* 创建socket跟设备进行通信*/
    client_addr.sin_family      = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(IpBuf);   //无限制
    client_addr.sin_port        = htons(8000);

    if ((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
            printf("socket error\n");
            exit(-1);
        }
    sin_size = sizeof(struct sockaddr_in);
    //setsockopt(client_sockfd,SOL_SOCKET,SO_RCVTIMEO,&time_out,sizeof(time_out));   //设置接收数据超时
    //setsockopt(client_sockfd,SOL_SOCKET,SO_SNDTIMEO,&time_out,sizeof(time_out));   //设置发送数据超时
    }

    /*启动定时器，每隔5S查看设备状态和系统状态*/
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CheckMachineStatFunction()));

    /* 启动定时器，更新时间*/
    systimer = new QTimer(this);
    connect(systimer, SIGNAL(timeout()), this, SLOT(UpdateWallTimeFunction()));

    /* 进度条*/
    processdlg          =   new QProgressDialog(this);

    /* 选择要更新的文件*/
    FileDialog          = new QFileDialog(this);

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

    /* 时间校准*/
    connect(ui->TimeAdjustButton, SIGNAL(clicked()), this, SLOT(TimeAdjustFunction()));

    /* 重新连接*/
    connect(ui->ReConnectButton, SIGNAL(clicked()), this, SLOT(ReConnectFunction()));

    /* 启动定时器*/
    timer->start(5000);
    systimer->start(1000);

    /* 初始化超时处理*/
    vt.tv_sec   =   15;
    vt.tv_usec  =   0;
}

MainWindow::~MainWindow()
{
    ::close(client_sockfd); //关闭网络
    delete ui;
}


