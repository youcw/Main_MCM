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

public:
    /* 网络通信变量*/
    int client_sockfd;
    int len;
    int sin_size;
    char buf[BUF_SIZE];
    struct sockaddr_in client_addr;

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

    /* 查看设备状态*/
    struct CheckMachineStat MachineInfo;

    /* 查看寄存器*/
    struct RegisterControl RegsInfo;

    /* 软件更新*/
    struct SoftWareUpdate SW_Update;

    /* 查看EEPROM*/
    struct EepromControl EepromInfo;

    /* GPRS短信息*/
    struct GprsMessage GprsMessageInfo;

    /* ZIGBEE信息*/
    struct ZigbeeMessage ZigbeeMessageInfo;

    /* 报警器控制 */
    struct BeepControl  BeepInfo;

    /* LED控制*/
    struct LedControl   LedInfo;

    /* 硬件自检*/
    struct HardWareTestSelf HardWareInfo;

    /* 时间校准*/
    struct TimeAdjust       TimeInfo;
};

#endif // MAINWINDOW_H
