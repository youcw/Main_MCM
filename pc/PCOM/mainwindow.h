#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/* 网络数据头文件*/
#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>


#include <QMainWindow>
#include <QtDebug>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>
#include <QDateTime>
#include <QProgressDialog>

#include "msg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init(void);
    int send_req_message(void *message, int length);
    int recv_rsp_message(void *message, int length);
    void init_uart(void);

private:
    Ui::MainWindow *ui;

private slots:
    void CheckMachineStatFunction(void);
    void RegisterSettingFunction(void);
    void EepromSettingFunction(void);
    void SendGprsMessageFunction(void);
    void SendZigbeeMessageFunction(void);
    void BeepSettingFunction(void);
    void LedSettingFunction(void);
    void HardWareTestSelfFunction(void);
    void SoftWareUpdateFunction(void);
    void UpdateWallTimeFunction(void);
    void TimeAdjustFunction(void);
    void ReConnectFunction(void);
public:
    int TransFlag;  /* 0: net; 1:uart*/
    char IpBuf[20];
    char UartBuf[20];
    /* 串口通信*/
    int uartfd;

    /* 网络通信变量*/
    int client_sockfd;
    int len;
    int sin_size;
    char buf[BUF_SIZE];
    struct sockaddr_in client_addr;

    fd_set readfd;
    struct timeval  vt;

    bool ok;

    /* 定时器*/
    QTimer *timer;
    QTimer *systimer;

    /* 文件操作*/
    QFileDialog *FileDialog;
    QFileInfo   *FileInfo;
    QFile       *File;

    /* 显示进度条*/
    QProgressDialog    *processdlg;

};

#endif // MAINWINDOW_H
