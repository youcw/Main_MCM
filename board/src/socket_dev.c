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
        pBoardStat->CheckMachineStatMsg.MsgId   = ARM_PC_CHECKMACHINESTAT_RSP;
        
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
        pregs->RegsMsg.MsgId            = ARM_PC_RegisterControl_Rsp;
        
        buf[0] = pregs->Addr;
        buf[1] = pregs->Data;
        printf("addr = %#x data = %#x flag = %d\n", buf[0], buf[1], pregs->flag);
        if(pregs->flag == READ)
                ioctl(regeditorfd, REGEDITOR_READ, buf);
        else
                ioctl(regeditorfd, REGEDITOR_WRITE, buf);
}

/* 功能：软件更新
 * 参数：同上
 * 返回值：无
 * */
void sw_update(char *pskb)
{
        struct SoftWareUpdate *psoftwareupdate = (struct SoftWareUpdate *)pskb;

}

/* 功能：获取温度
 * 参数：同上
 * 返回值：无
 * */
void get_temperature(char *pskb)
{
        struct  GetTempData *pgettempdata = (struct GetTempData *)pskb;

        pgettempdata->TempData = get_ds18b20_temperature(); 
}

/* 功能：获取电压
 * 参数：同上
 * 返回值：无
 * */
void get_voltage(char *pskb)
{
        struct GetVoltageData *pgetvoltagedata = (struct GetVoltageData *)pskb;

        pgetvoltagedata->VoltageData = get_adc_voltage();
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
        struct GprsMessage *pgprsmessage = (struct GprsMessage *)pskb;

        pgprsmessage->SendResult = send_gprs_message(pgprsmessage->TelephoneNumber, pgprsmessage->Message);
}

/* 功能：上位机发送zigbee信息
 * 参数：同上
 * 返回值:无
 * */
void send_zigbee_message_req(char *pskb)
{
        struct ZigbeeMessage *pZigbeeMessage = (struct ZigbeeMessage*)pskb;

        pZigbeeMessage->SendResult = send_zigbee_message(pZigbeeMessage->Message);
}

/* 功能:报警器控制
 * 参数：同上
 * 返回值：无
 * */
void beep_control_req(char *pskb)
{
        struct BeepControl *pBeep = (struct BeepControl*)pskb;
        
        if(pBeep->Flag == 1) { //打开
                pBeep->SendResult = start_alarm();
        } else {        //关闭
                pBeep->SendResult = stop_alarm(); 
        }
}

/* 功能:LED控制
 * 参数：同上
 * 返回值：无
 * */
void led_control_req(char *pskb)
{
        struct LedControl *pLed = (struct LedControl *)pskb;

        if (pLed->Flag == 1) {
                pLed->SendResult = start_led(pLed->FlashTime);
        } else {
                pLed->SendResult = stop_led();
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
