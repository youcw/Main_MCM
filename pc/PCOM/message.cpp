#include "mainwindow.h"
#include "ui_mainwindow.h"


/* 关闭设备，不要应用QT4的close*/
extern int close (int __fd);
extern int init_device(int *fd,char *buf);
extern void init_serial(int *fd);
/* 定时查看设备状态*/
void MainWindow::CheckMachineStatFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_machine_info_req rMachineInfoReq;
    struct stru_machine_info_rsp rMachineInfoRsp;

    /* 构造消息请求*/
    rMachineInfoReq.struMsgHeader.u16MsgType  = O_MCMMAIN_MACHINE_INFO_QUERY_REQ;
    rMachineInfoReq.struMsgHeader.u16MsgLength = sizeof(rMachineInfoReq)
                                                - sizeof(rMachineInfoReq.struMsgHeader);
    rMachineInfoReq.struMsgHeader.u8TransType   =   TransFlag;

    /* 发送消息*/
    if (send_req_message(&rMachineInfoReq, sizeof(rMachineInfoReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rMachineInfoRsp, sizeof(rMachineInfoRsp)) == -1)
        return;

    qDebug("cpufreq = %f\n", rMachineInfoRsp.f32CpuFreq);
    /* 解析消息并填充界面信息*/
    if (rMachineInfoRsp.struMsgHeader.u16MsgType
                    != O_MAINMCM_MACHINE_INFO_QUERY_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    ui->StatButton->setText(tr("正常"));

    /* 显示温度*/
    ui->CurrnetTemperatureLineEdit->setText(QString::number(rMachineInfoRsp.f32Temp, 'g', 3));

    /* 显示电压*/
    ui->CurrentVoltageLineEdit->setText(QString::number(rMachineInfoRsp.f32Vol, 'g', 3));

    /* 显示CPU频率*/
    ui->CpuFreqLineEdit->setText(QString::number(rMachineInfoRsp.f32CpuFreq, 'g', 3));

    /* 显示剩余内存*/
    ui->FreeMemLineEdit->setText(QString::number(rMachineInfoRsp.u32FreeMem, 10));

    /* 显示剩余磁盘空间*/
    ui->FreeDiskSpaceLineEdit->setText(QString::number(rMachineInfoRsp.u32FreeDisk, 10));
}

/* 寄存器操作*/
void MainWindow::RegisterSettingFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_set_register_data_req rSetRegisterDataReq;
    struct stru_set_register_data_rsp rSetRegisterDataRsp;
    struct stru_get_register_data_req rGetRegisterDataReq;
    struct stru_get_register_data_rsp rGetRegisterDataRsp;

    if(ui->RegisterWriteCheckBox->isChecked() == true) { //设置
        /* 构造请求消息*/
        rSetRegisterDataReq.struMsgHeader.u16MsgType   =   O_MCMMAIN_SET_REGISTER_DATA_REQ;
        rSetRegisterDataReq.struMsgHeader.u16MsgLength =   sizeof(rSetRegisterDataReq)
                                                            - sizeof(rSetRegisterDataReq.struMsgHeader);
        rSetRegisterDataReq.u32Offset                  =   ui->RegisterAddrLineEdit->displayText().toULong(&ok, 16);
        if (ok == false) {
            QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
            return;
        }

        rSetRegisterDataReq.u32RegisterData            = ui->RegisterDataLineEdit->displayText().toULong(&ok, 16);
        if (ok == false) {
            QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
            return;
        }
        qDebug("addr = %#x data = %#x\n", rSetRegisterDataReq.u32Offset, rSetRegisterDataReq.u32RegisterData);
        rSetRegisterDataReq.struMsgHeader.u8TransType   =   TransFlag;

        /* 发送消息*/
        if (send_req_message(&rSetRegisterDataReq, sizeof(rSetRegisterDataReq)) == -1)
            return;

        /* 接收并处理消息*/
        if (recv_rsp_message(&rSetRegisterDataRsp, sizeof(rSetRegisterDataRsp)) == -1)
            return;

        if (rSetRegisterDataRsp.struMsgHeader.u16MsgType != O_MAINMCM_SET_REGISTER_DATA_RSP) {
            QMessageBox::question(this, tr("结果"), QString(tr("消息错误")));
            return;
        }

        if (rSetRegisterDataRsp.bSuccessful ==  SYS_ERROR) {
            QMessageBox::question(this, tr("结果"), QString(tr("配置失败")));
            return;
        } else
            QMessageBox::question(this, tr("结果"), QString(tr("配置成功")));
    } else if (ui->RegisterReadCheckBox->isChecked() == true) { //获取
        /* 构造请求消息*/
        rGetRegisterDataReq.struMsgHeader.u16MsgType   =   O_MCMMAIN_GET_REGISTER_DATA_REQ;
        rGetRegisterDataReq.struMsgHeader.u16MsgLength =   sizeof(rGetRegisterDataReq)
                                                            - sizeof(rGetRegisterDataReq.struMsgHeader);
        rGetRegisterDataReq.u32Offset                  =   ui->RegisterAddrLineEdit->displayText().toULong(&ok, 16);
        if (ok == false) {
            QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
            return;
        }

        /* 发送消息*/
        rGetRegisterDataReq.struMsgHeader.u8TransType   =   TransFlag;

        if (send_req_message(&rGetRegisterDataReq, sizeof(rGetRegisterDataReq)) == -1)
            return;

        /* 接收并处理消息*/
        if (recv_rsp_message(&rGetRegisterDataRsp, sizeof(rGetRegisterDataRsp)) == -1)
            return;

        if (rGetRegisterDataRsp.struMsgHeader.u16MsgType != O_MAINMCM_GET_REGISTER_DATA_RSP) {
            QMessageBox::question(this, tr("结果"), QString(tr("消息错误")));
            return;
        }
        ui->RegisterDataLineEdit->setText(QString::number(rGetRegisterDataRsp.u32RegisterData, 16));
    } else {
        QMessageBox::question(this, tr("结果"),QString(tr("选择读写方式")));
        return;
    }
}

/* EEPROM设置*/
void MainWindow::EepromSettingFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_set_eeprom_data_req rSetEepromDataReq;
    struct stru_set_eeprom_data_rsp rSetEepromDataRsp;
    struct stru_get_eeprom_data_req rGetEepromDataReq;
    struct stru_get_eeprom_data_rsp rGetEepromDataRsp;
    int i;
    u32 Data;

    memset(&rSetEepromDataRsp, 0, sizeof(rSetEepromDataRsp));
    memset(&rGetEepromDataRsp, 0, sizeof(rGetEepromDataRsp));

    if(ui->EepromWriteCheckBox->isChecked() == true) {
       /* 构造消息 */
       rSetEepromDataReq.struMsgHeader.u16MsgType   =   O_MCMMAIN_SET_EEPROM_DATA_REQ;
       rSetEepromDataReq.struMsgHeader.u16MsgLength =   sizeof(rSetEepromDataReq)
                                                            - sizeof(rSetEepromDataReq.struMsgHeader);
       rSetEepromDataReq.u16Offset                  =   ui->EepromAddrLineEdit->displayText().toULong(&ok, 16);
       if(ok == false) {
           QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
           return;
       }

       Data = ui->EepromDataLineEdit->displayText().toULong(&ok, 16);
       if(ok == false) {
           QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
           return;
       }

       memcpy(rSetEepromDataReq.u8EepromData, &Data, sizeof(rSetEepromDataReq.u8EepromData));
        rSetEepromDataReq.struMsgHeader.u8TransType   =   TransFlag;
        /* 发送消息*/
        if(send_req_message(&rSetEepromDataReq, sizeof(rSetEepromDataReq)) == -1)
            return;

        /* 接收并处理消息*/
        if (recv_rsp_message(&rSetEepromDataRsp, sizeof(rSetEepromDataRsp)) == -1)
            return;

       if (rSetEepromDataRsp.struMsgHeader.u16MsgType != O_MAINMCM_SET_EEPROM_DATA_RSP) {
           QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
           //return;
       }

       if (rSetEepromDataRsp.bSuccessful == SYS_ERROR) {
           QMessageBox::question(this, tr("结果"),QString(tr("配置失败")));
       } else
           QMessageBox::question(this, tr("结果"),QString(tr("配置成功")));
       return;

    } else if (ui->EepromReadCheckBox->isChecked() == true) {
       /* 构造请求消息*/
        rGetEepromDataReq.struMsgHeader.u16MsgType      =   O_MCMMAIN_GET_EEPROM_DATA_REQ;
        rGetEepromDataReq.struMsgHeader.u16MsgLength    =   sizeof(rGetEepromDataReq)
                                                                - sizeof(rGetEepromDataReq.struMsgHeader);
        rGetEepromDataReq.u16Offset                     =   ui->EepromAddrLineEdit->displayText().toULong(&ok, 16);
        if(ok == false) {
            QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
            return;
        }

        rGetEepromDataReq.struMsgHeader.u8TransType = TransFlag;
        /* 发送消息*/
        if (send_req_message(&rGetEepromDataReq, sizeof(rGetEepromDataReq)) == -1)
            return;

        /* 接收并处理消息*/
        if (recv_rsp_message(&rGetEepromDataRsp, sizeof(rGetEepromDataRsp)) == -1)
            return;

        if (rGetEepromDataRsp.struMsgHeader.u16MsgType  != O_MAINMCM_GET_EEPROM_DATA_RSP) {
            QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
            //return;
        }

        memcpy(&Data, rGetEepromDataRsp.u8EepromData, sizeof(rGetEepromDataRsp.u8EepromData));
        ui->EepromDataLineEdit->setText(QString::number(Data, 16));
        return;
    } else
        QMessageBox::question(this, tr("结果"), QString(tr("选择操作方式")));
}

/* 发送GRPS短信息*/
void MainWindow::SendGprsMessageFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_send_gprs_message_req   rSendGprsMessageReq;
    struct stru_send_gprs_message_rsp   rSendGprsMessageRsp;

    /* 构造请求消息*/
    rSendGprsMessageReq.struMsgHeader.u16MsgType       = O_MCMMAIN_MODEM_REQ;
    rSendGprsMessageReq.struMsgHeader.u16MsgLength     = sizeof(rSendGprsMessageReq)
                                                            - sizeof(rSendGprsMessageReq.struMsgHeader);

    strcpy(rSendGprsMessageReq.s8PhoneNum,
            ui->TelephoneNumberLineEdit->displayText().toLocal8Bit());
    //str.toLatin1().data()
    strcpy(rSendGprsMessageReq.s8MessageInfo,
            ui->MessageLineEdit->displayText().toLocal8Bit());
    rSendGprsMessageReq.struMsgHeader.u8TransType   =   TransFlag;

    /* 发送消息*/
    if (send_req_message(&rSendGprsMessageReq, sizeof(rSendGprsMessageReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rSendGprsMessageRsp, sizeof(rSendGprsMessageRsp)) == -1)
        return;

    if (rSendGprsMessageRsp.struMsgHeader.u16MsgType != O_MAINMCM_MODEM_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rSendGprsMessageRsp.bSuccessful == SYS_ERROR)
        QMessageBox::question(this, tr("结果"),QString(tr("发送信息失败")));
    else
        QMessageBox::question(this, tr("结果"),QString(tr("发送信息成功")));
}

/* 发送zigbee控制命令*/
void MainWindow::SendZigbeeMessageFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_send_zigbee_message_req     rSendZigbeeMessageReq;
    struct stru_send_zigbee_message_rsp     rSendZigbeeMessageRsp;

    /* 构造请求消息*/
    rSendZigbeeMessageReq.struMsgHeader.u16MsgType = O_MCMMAIN_ZIGBEE_REQ;
    rSendZigbeeMessageReq.struMsgHeader.u16MsgLength = sizeof(rSendZigbeeMessageReq)
                                                            - sizeof(rSendZigbeeMessageReq.struMsgHeader);
    strcpy(rSendZigbeeMessageReq.s8MessageInfo,
                                ui->ZigbeeMessageLineEdit->displayText().toLocal8Bit());
    rSendZigbeeMessageReq.struMsgHeader.u8TransType   =   TransFlag;
    /* 发送消息*/
    if (send_req_message(&rSendZigbeeMessageReq, sizeof(rSendZigbeeMessageReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rSendZigbeeMessageRsp, sizeof(rSendZigbeeMessageRsp)) == -1)
        return;

    if (rSendZigbeeMessageRsp.struMsgHeader.u16MsgType != O_MAINMCM_ZIGBEE_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rSendZigbeeMessageRsp.bSuccessful == SYS_ERROR)
        QMessageBox::question(this, tr("结果"),QString(tr("发送信息失败")));
    else
        QMessageBox::question(this, tr("结果"),QString(tr("发送信息成功")));
}

/* 报警器控制*/
void MainWindow::BeepSettingFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_beep_control_req    rBeepCtrlReq;
    struct stru_beep_control_rsp    rBeepCtrlRsp;

    /* 构造请求消息*/
    rBeepCtrlReq.struMsgHeader.u16MsgType   = O_MCMMAIN_BEEP_REQ;
    rBeepCtrlReq.struMsgHeader.u16MsgLength = sizeof(rBeepCtrlReq)
                                                - sizeof(rBeepCtrlReq.struMsgHeader);
    rBeepCtrlReq.struMsgHeader.u8TransType   =   TransFlag;


    if(ui->BeepOpenCheckBox->isChecked() == true) {
        rBeepCtrlReq.u8BeepCtrlOperation    =   1;
    } else if(ui->BeepCloseCheckBox->isChecked() == true) {
        rBeepCtrlReq.u8BeepCtrlOperation    = 0;
    } else {
       QMessageBox::question(this, tr("结果"), QString(tr("选择操作方式")));
       return;
    }

    /* 发送消息*/
    if (send_req_message(&rBeepCtrlReq, sizeof(rBeepCtrlReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rBeepCtrlRsp, sizeof(rBeepCtrlRsp)) == -1)
        return;

    if (rBeepCtrlRsp.struMsgHeader.u16MsgType != O_MAINMCM_BEEP_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rBeepCtrlRsp.bSuccessful == SYS_ERROR)
        QMessageBox::question(this, tr("结果"),QString(tr("配置失败")));
    else
        QMessageBox::question(this, tr("结果"),QString(tr("配置成功")));
}

/* LED 控制*/
void MainWindow::LedSettingFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_led_control_req     rLedCtrlReq;
    struct stru_led_control_rsp     rLedCtrlRsp;

    /* 构造消息*/
    rLedCtrlReq.struMsgHeader.u16MsgType    = O_MCMMAIN_LED_REQ;
    rLedCtrlReq.struMsgHeader.u16MsgLength  = sizeof(rLedCtrlReq)
                                                - sizeof(rLedCtrlReq.struMsgHeader);

    rLedCtrlReq.u8LedType                   =   2;      //暂时添加为运行灯
    rLedCtrlReq.struMsgHeader.u8TransType   =   TransFlag;
    if (ui->LedOpenCheckBox->isChecked() == true) {
        rLedCtrlReq.u8LedCmd    =   1;
    } else if (ui->LedCloseCheckBox->isChecked() == true) {
        rLedCtrlReq.u8LedCmd    =   0;
    } else {
        QMessageBox::question(this, tr("结果"), QString(tr("选择操作方式")));
        return;
    }

    if((rLedCtrlReq.u8LedCmd != 0) && (rLedCtrlReq.u8LedCmd != 1) ) {
        rLedCtrlReq.u32BlinkTime = ui->LedFlashTimeLineEdit->displayText().toULong(&ok, 10);
        if (ok == false) {
            QMessageBox::question(this, tr("结果"),QString(tr("数据类型转换失败")));
            return;
        }
    }
    /* 发送消息*/
    if (send_req_message(&rLedCtrlReq, sizeof(rLedCtrlReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rLedCtrlRsp, sizeof(rLedCtrlRsp)) == -1)
        return;

    if (rLedCtrlRsp.struMsgHeader.u16MsgType != O_MAINMCM_LED_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rLedCtrlRsp.bSuccessful == SYS_ERROR)
        QMessageBox::question(this, tr("结果"),QString(tr("配置失败")));
    else
        QMessageBox::question(this, tr("结果"),QString(tr("配置成功")));
}

/* 设备自检查询*/
void MainWindow::HardWareTestSelfFunction(void)
{
    qDebug("%s", __FUNCTION__);

    struct stru_selftest_req    rSelfTestReq;
    struct stru_selftest_rsp    rSelfTestRsp;

    /* 构造请求消息*/
    rSelfTestReq.struMsgHeader.u16MsgType   = O_MCMMAIN_HARDWARE_SELFTEST_REQ;
    rSelfTestReq.struMsgHeader.u16MsgLength = sizeof(rSelfTestReq)
                                                - sizeof(rSelfTestReq.struMsgHeader);
    rSelfTestReq.struMsgHeader.u8TransType   =   TransFlag;

    /* 发送消息*/
    if (send_req_message(&rSelfTestReq, sizeof(rSelfTestReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rSelfTestRsp, sizeof(rSelfTestRsp)) == -1)
        return;

    if (rSelfTestRsp.struMsgHeader.u16MsgType != O_MAINMCM_HARDWARE_SELFTEST_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rSelfTestRsp.s32SelfTestResult  != 0)
           ui->HardWareTestSelfLineEdit->setText(tr("异常"));
    else
           ui->HardWareTestSelfLineEdit->setText(tr("正常"));
}

/* 软件更新*/
void MainWindow::SoftWareUpdateFunction(void)
{
    int fd          = -1;
    int xferedlen     = 0;
    struct stru_software_update_req rSoftWareUpdateReq;
    struct stru_software_update_rsp rSoftWareUpdateRsp;

    /* 选择更新的文件*/
    QString FileName = FileDialog->getOpenFileName(this);
    if (FileName.isEmpty()) {
        QMessageBox::question(this, tr("结果"),QString(tr("请选择更新文件")));
        return;
    }

    /* 获取文件属性*/
    File     = new QFile(FileName);
    FileInfo = new QFileInfo(FileName);
    processdlg->setRange(0, File->size());

    /* 打开文件*/
    fd = open(File->fileName().toLocal8Bit(), O_RDONLY);
    if(fd < 0) {
        QMessageBox::question(this, tr("结果"),QString(tr("打开文件失败")));
        return;
    }

    strcpy(rSoftWareUpdateReq.s8FileName, FileInfo->fileName().toLocal8Bit());

    /* 传输文件，每次传输5K*/
    while ((rSoftWareUpdateReq.u32Len = read(fd, rSoftWareUpdateReq.u8Buffer, BUF_SIZE)) > 0) {
        /* 构造请求消息*/
        rSoftWareUpdateReq.struMsgHeader.u16MsgType     = O_MCMMAIN_SOFTWARE_UPDATE_REQ;
        rSoftWareUpdateReq.struMsgHeader.u16MsgLength   = sizeof(rSoftWareUpdateReq)
                                                            - sizeof(rSoftWareUpdateReq.struMsgHeader);
    rSoftWareUpdateReq.struMsgHeader.u8TransType   =   TransFlag;
        /* 发送消息*/
    if (send_req_message(&rSoftWareUpdateReq, sizeof(rSoftWareUpdateReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rSoftWareUpdateRsp, sizeof(rSoftWareUpdateRsp)) == -1)
        return;

        /* 解析反馈结果*/
        if(rSoftWareUpdateRsp.struMsgHeader.u16MsgType == O_MAINMCM_SOFTWARE_UPDATE_RSP) {
            if(rSoftWareUpdateRsp.bSuccessful == SYS_ERROR) {
                QMessageBox::question(this, tr("更新结果"),QString(tr("更新失败")));
                return;
            } else {
                /* 显示进度*/
                xferedlen += rSoftWareUpdateReq.u32Len;
                processdlg->setValue(xferedlen);
                if (xferedlen == File->size())
                    QMessageBox::question(this, tr("更新结果"),QString(tr("更新成功")));
            }
        }
        bzero(rSoftWareUpdateReq.u8Buffer, rSoftWareUpdateReq.u32Len);
    }
    ::close(fd);
}

/* 更新系统界面时间*/
void MainWindow::UpdateWallTimeFunction(void)
{
    ui->CurrentTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

/* 校准时间*/
void MainWindow::TimeAdjustFunction(void)
{
    QDate   date;
    QTime   time;
    struct stru_tod_adjust_req  rTodAdjustReq;
    struct stru_tod_adjust_rsp  rTodAdjustRsp;

    /* 获取日期信息*/
    date    =   ui->dateTimeEdit->date();
    time    =   ui->dateTimeEdit->time();

    /* 构造消息*/
    rTodAdjustReq.struMsgHeader.u16MsgType      = O_MCMMAIN_TOD_ADJUST_REQ;
    rTodAdjustReq.struMsgHeader.u16MsgLength    = sizeof(rTodAdjustReq)
                                                    - sizeof(rTodAdjustReq.struMsgHeader);
    /* 解析年月日时分秒*/
    rTodAdjustReq.struTimeInfo.u16Year          =  date.year();
    rTodAdjustReq.struTimeInfo.u16Month         =  date.month();
    rTodAdjustReq.struTimeInfo.u8Day            =  date.day();
    rTodAdjustReq.struTimeInfo.u8Hour           =  time.hour();
    rTodAdjustReq.struTimeInfo.u8Minute         =  time.minute();
    rTodAdjustReq.struTimeInfo.u8Second         =  time.second();

    rTodAdjustReq.struMsgHeader.u8TransType   =   TransFlag;
    /* 发送消息*/
    if (send_req_message(&rTodAdjustReq, sizeof(rTodAdjustReq)) == -1)
        return;

    /* 接收并处理消息*/
    if (recv_rsp_message(&rTodAdjustRsp, sizeof(rTodAdjustRsp)) == -1)
        return;

    if (rTodAdjustRsp.struMsgHeader.u16MsgType != O_MAINMCM_TOD_ADJUST_RSP) {
        QMessageBox::question(this, tr("结果"),QString(tr("消息错误")));
        return;
    }

    if (rTodAdjustRsp.bSuccessful == SYS_ERROR)
        QMessageBox::question(this, tr("结果"),QString(tr("配置失败")));
    else
        QMessageBox::question(this, tr("结果"),QString(tr("配置成功")));
}

/* 重新连接*/
void MainWindow::ReConnectFunction(void)
{
    qDebug("%s\n", __FUNCTION__);
    init_uart();
}

/* TODO：如何实现软件版本查询*/

int MainWindow::send_req_message(void *message, int length)
{
    if (TransFlag == TRANSFER_UART)
    {
        len = write(uartfd, message, length);
            if (len < 0) {
                QMessageBox::question(this, tr("结果"),QString(tr("发送串口数据失败")));
                return -1;
            }
    }
    else {
            len  = sendto(client_sockfd, message, length,
                                        0, (struct sockaddr *)&client_addr, sin_size);
            if (len < 0) {
                QMessageBox::question(this, tr("结果"),QString(tr("发送网络数据失败")));
                return -1;
            }
        }
    return 0;
}

int MainWindow::recv_rsp_message(void *message, int length)
{

    int ret;
    int fd;
    int remain = length;
    int rsize = 0;      //已读数据大小
    void *pbuf = message;

    /*设置超时时间*/
    vt.tv_sec   =   15;
    vt.tv_usec  =   0;

    memset(pbuf, 0, length);

    FD_ZERO(&readfd);
    fd = uartfd > client_sockfd ? uartfd : client_sockfd;
    FD_SET(fd, &readfd);

    ret = select(fd + 1, &readfd, NULL, NULL, &vt);
    if (ret == 0) {
        QMessageBox::question(this, tr("结果"), QString(tr("接收数据超时")));
        return -1;
    } else if(ret < 0) {
        QMessageBox::question(this, tr("结果"), QString(tr("出错")));
        return -1;
    } else {
        if (TransFlag == TRANSFER_UART) {
            while(remain > 0){
                    //usleep(200000);  
                    rsize = read(uartfd, pbuf, remain);
                    qDebug("read %d byte data\n", rsize);
                    if (rsize < 0 ) {
                            QMessageBox::question(this, tr("结果"),QString(tr("接收串口数据失败")));
                            return -1;
                        }
                    remain -= rsize;
                    pbuf += rsize;
                }

            } else if (TransFlag == TRANSFER_NET){
            len = recvfrom(client_sockfd, message, length, 0, 0, 0);
            if (len < 0) {
                QMessageBox::question(this, tr("结果"),QString(tr("接收网络数据失败")));
                return -1;
            }
        }
    }
    return 0;
}

void MainWindow::init_uart(void)
{
    init_device(&uartfd,UartBuf);
    init_serial(&uartfd);
}
