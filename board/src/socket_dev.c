#include <stdio.h>
#include "common.h"
#include "msg.h"
#include "log.h"
#include "device.h"

/* 功能：获取系统运行状态 
 * 参数: pskb网络数据指针 
 * 返回值：无
 * */
void get_machine_stat(char *pskb)
{
        struct CheckMachineStat *pBoardStat     = (struct CheckMachineStat*)pskb;
       
        /* 填充消息结构*/
        pBoardStat->CheckMachineStatMsg.MsgId   = ARM_PC_CHECK_MACHINE_STAT_RSP;
        pBoardStat->CheckMachineStatMsg.MsgLen  = sizeof(*pBoardStat) 
                                                    - sizeof(pBoardStat->CheckMachineStatMsg);

        pBoardStat->MachineStat                 = 1;
        pBoardStat->TempData                    = get_ds18b20_temperature();
        pBoardStat->Voltage                     = get_adc_voltage();
        pBoardStat->CpuFreq                     = get_cpu_freq();
        pBoardStat->FreeMemSpace                = get_freemem_space();
        pBoardStat->FreeDiskSpace               = get_freedisk_space();
}

/* 
 * 功能：进行处理网络数据，关于寄存器操作
 * 参数：pskb:网络数据指针
 * 返回值：无
 * */
void register_xfer(char *pskb)
{
        unsigned long buf[3];

        struct RegisterControl *pregs   = (struct RegisterControl *)pskb;
        
        /*填充消息*/
        pregs->RegsMsg.MsgId            = ARM_PC_REGISTER_RW_RSP;
        pregs->RegsMsg.MsgLen           = sizeof(*pregs)
                                            - sizeof(pregs->RegsMsg);
        
        buf[0] = pregs->Addr;
        buf[1] = pregs->Data;
        if(pregs->flag == READ)
                pregs->Result = ioctl(regeditorfd, REGEDITOR_READ, buf);
        else
                pregs->Result = ioctl(regeditorfd, REGEDITOR_WRITE, buf);
}

/* 功能：软件更新
 * 参数：同上
 * 返回值：无
 * */
void sw_update(char *pskb)
{
        int fd;
        int ssize;

        struct SoftWareUpdate *psoftwareupdate      = (struct SoftWareUpdate *)pskb;
    
        /* 消息处理*/
        psoftwareupdate->SoftWareUpdateMsg.MsgId    = ARM_PC_SOFTWARE_UPDATE_RSP;
        psoftwareupdate->SoftWareUpdateMsg.MsgLen   = sizeof(*psoftwareupdate)
                                                        - sizeof(psoftwareupdate->SoftWareUpdateMsg);

        fd = open(psoftwareupdate->FileName, O_CREAT | O_WRONLY | O_APPEND, 0644); 
        if (fd < 0) {
            ERROR("open %s file error\n", psoftwareupdate->FileName);
            return;
        }
        
        ssize = write(fd, psoftwareupdate->buf, psoftwareupdate->Len); 
        if (ssize < 0) {
            ERROR("write %s file error\n", psoftwareupdate->FileName);
            return;
        }
        close(fd);
}

/* 功能：操作EEPROM
 * 参数：同上
 * 返回值：无
 * */
void eeprom_xfer(char *pskb)
{
        unsigned long buf[2];

        struct ControlEeprom *peeprom = (struct ControlEeprom *)pskb;

        buf[0] = peeprom->addr;
        buf[1] = peeprom->data;
        if(peeprom->flag == READ) {
                ioctl(eepromfd, EEPROM_READ, buf);
        } else {
                ioctl(eepromfd, EEPROM_WRITE, buf);
        }
}

/* 功能：上位机发GPRS短信息命令
 * 参数：同上
 * 返回值：无
 * */
void send_gprs_message_req(char *pskb)
{
        struct GprsMessage *pgprsmessage    = (struct GprsMessage *)pskb;

        /* 构造消息*/
        pgprsmessage->GprsMessageMsg.MsgId  = ARM_PC_SEND_GPRS_MESSAGE_RSP;
        pgprsmessage->GprsMessageMsg.MsgLen = sizeof(*pgprsmessage)
                                                - sizeof(pgprsmessage->GprsMessageMsg);

        pgprsmessage->Result = send_gprs_message(pgprsmessage->TelephoneNumber, 
                                                        pgprsmessage->Message);
}

/* 功能：上位机发送zigbee信息
 * 参数：同上
 * 返回值:无
 * */
void send_zigbee_message_req(char *pskb)
{
        struct ZigbeeMessage *pZigbeeMessage    = (struct ZigbeeMessage*)pskb;

        /* 消息处理*/
        pZigbeeMessage->ZigbeeMessageMsg.MsgId  = ARM_PC_SEND_ZIGBEE_MESSAGE_RSP;
        pZigbeeMessage->ZigbeeMessageMsg.MsgLen = sizeof(*pZigbeeMessage)
                                                    - sizeof(pZigbeeMessage->ZigbeeMessageMsg);

       // pZigbeeMessage->Result = send_zigbee_message(pZigbeeMessage->Message);
}

/* 功能:报警器控制
 * 参数：同上
 * 返回值：无
 * */
void beep_control_req(char *pskb)
{
        struct BeepControl *pBeep       = (struct BeepControl*)pskb;
        
        /* 消息处理*/
        pBeep->BeepControlMsg.MsgId     = ARM_PC_BEEP_CONTROL_RSP;
        pBeep->BeepControlMsg.MsgLen    = sizeof(*pBeep)
                                            - sizeof(pBeep->BeepControlMsg);
        if(pBeep->Flag == 1) { //打开
                pBeep->Result = start_alarm();
        } else {        //关闭
                pBeep->Result = stop_alarm(); 
        }
}

/* 功能:LED控制
 * 参数：同上
 * 返回值：无
 * */
void led_control_req(char *pskb)
{
        struct LedControl *pLed     = (struct LedControl *)pskb;

        /* 消息处理*/
        pLed->LedControlMsg.MsgId   = ARM_PC_LEDS_CONTROL_RSP;
        pLed->LedControlMsg.MsgLen  = sizeof(*pLed)
                                        - sizeof(pLed->LedControlMsg);

        if (pLed->Flag == 1) {
                pLed->Result = flash_led(pLed->FlashTime);
        } else {
                pLed->Result = stop_led();
        }
}

/* 功能:硬件自检
 * 参数：同上
 * 返回值:无
 * */
void hardware_selftest_req(char *pskb)
{
       struct HardWareTestSelf *pHardWareTestSelf = (struct HardWareTestSelf *)pskb;

       pHardWareTestSelf->HardWareTestSelfMsg.MsgId = ARM_PC_HARDWARE_TESTSELF_RSP;
       pHardWareTestSelf->HardWareTestSelfMsg.MsgLen = 0;
}

/* 功能：时间校准
 * 参数：同上
 * 返回值：无
 * */
void time_adjust(char *pskb)
{
        struct tm tm;
        time_t  tt;
        struct timeval tv;

        struct TimeAdjust   *pTimeInfo      = (struct TimeAdjust *)pskb;
    
        pTimeInfo->TimeAdjustMsg.MsgId      = ARM_PC_TIME_ADJUST_RSP;
        pTimeInfo->TimeAdjustMsg.MsgLen     = sizeof(*pTimeInfo)
                                                - sizeof(pTimeInfo->TimeAdjustMsg);
        tm.tm_sec  = pTimeInfo->sec;
        tm.tm_min  = pTimeInfo->min;
        tm.tm_hour = pTimeInfo->hour;
        tm.tm_mday = pTimeInfo->day;
        tm.tm_mon  = pTimeInfo->month;
        tm.tm_year = pTimeInfo->year - 1900;

        tt = mktime(&tm);
        if (tt == -1) 
            pTimeInfo->Result = -1;
        tv.tv_sec = (long)tt;
        tv.tv_usec = 0;

        pTimeInfo->Result = settimeofday(&tv,NULL);
}
