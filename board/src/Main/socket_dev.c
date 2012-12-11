#include <stdio.h>
#include "common.h"
#include "msg.h"
#include "log.h"
#include "device.h"
#include "socket.h"

/* 功能：获取系统运行状态 
 * 参数: MCM请求消息 
 * 返回值：无
 * */
void get_machine_info_req(s8 *pskb)
{
        struct stru_machine_info_req    *prMachineInfoReq = (struct stru_machine_info_req *)pskb;
        struct stru_machine_info_rsp    rMachineInfoRsp; 

        memset(&rMachineInfoRsp, 0, sizeof(rMachineInfoRsp));

        /* 构造反馈消息*/
        rMachineInfoRsp.struMsgHeader.u16MsgType        = O_MAINMCM_MACHINE_INFO_QUERY_RSP;
        rMachineInfoRsp.struMsgHeader.u16MsgLength      = sizeof(rMachineInfoRsp)
                                                                - sizeof(rMachineInfoRsp.struMsgHeader);
        rMachineInfoRsp.struMsgHeader.u8TransType       = prMachineInfoReq->struMsgHeader.u8TransType;
        get_ds18b20_temperature(&rMachineInfoRsp.f32Temp);
        get_adc_voltage(&rMachineInfoRsp.f32Vol);
        get_cpu_freq(&rMachineInfoRsp.f32CpuFreq);
        get_freemem_space(&rMachineInfoRsp.u32FreeMem);
        get_freedisk_space(&rMachineInfoRsp.u32FreeDisk);
        
        /* 反馈消息到MCM*/
        send_rsp_message(&rMachineInfoRsp, 
                                sizeof(rMachineInfoRsp), 
                                prMachineInfoReq->struMsgHeader.u8TransType);
}

/* 
 * 功能：设置register请求处理
 * 参数：MCM请求消息
 * 返回值：无
 * */
void set_register_data_req(s8 *pskb)
{
        u32 buf[2];
        struct stru_set_register_data_req *prSetRegisterDataReq = (struct stru_set_register_data_req *)pskb;
        struct stru_set_register_data_rsp rSetRegisterDataRsp;

        /*填充消息*/
        rSetRegisterDataRsp.struMsgHeader.u16MsgType            = O_MAINMCM_SET_REGISTER_DATA_RSP;
        rSetRegisterDataRsp.struMsgHeader.u16MsgLength          = sizeof(rSetRegisterDataRsp) 
                                                                        - sizeof(rSetRegisterDataRsp.struMsgHeader);
        rSetRegisterDataRsp.struMsgHeader.u8TransType           = prSetRegisterDataReq->struMsgHeader.u8TransType;       
        buf[0] = prSetRegisterDataReq->u32Offset;
        buf[1] = prSetRegisterDataReq->u32RegisterData;
  
        printf("addr = %#x data = %#x\n", buf[0], buf[1]);
        
        if (ioctl(regeditorfd, REGEDITOR_WRITE, buf) < 0)
                rSetRegisterDataRsp.bSuccessful = SYS_ERROR;
        else
                rSetRegisterDataRsp.bSuccessful = SYS_OK;
       
        /* 反馈消息到MCM*/
        send_rsp_message(&rSetRegisterDataRsp, 
                                sizeof(rSetRegisterDataRsp), 
                                prSetRegisterDataReq->struMsgHeader.u8TransType);
}

/* 功能：查询寄存器请求处理
 * 参数：MCM请求消息
 * 返回值：无
 */
void get_register_data_req(s8 *pskb)
{
        u32 buf[2];
        struct stru_get_register_data_req *prGetRegisterDataReq = (struct stru_get_register_data_req *)pskb;
        struct stru_get_register_data_rsp rGetRegisterDataRsp;

        /* 填充消息*/
        rGetRegisterDataRsp.struMsgHeader.u16MsgType            = O_MAINMCM_GET_REGISTER_DATA_RSP;
        rGetRegisterDataRsp.struMsgHeader.u16MsgLength          = sizeof(rGetRegisterDataRsp) 
                                                                        - sizeof(rGetRegisterDataRsp.struMsgHeader);
        rGetRegisterDataRsp.struMsgHeader.u8TransType           = prGetRegisterDataReq->struMsgHeader.u8TransType;
        buf[0] = prGetRegisterDataReq->u32Offset;

        if (ioctl(regeditorfd, REGEDITOR_READ, buf) < 0) 
                rGetRegisterDataRsp.u32RegisterData = 0xffffffff; //TODO：定义错误码
        else
                rGetRegisterDataRsp.u32RegisterData = buf[1];
        
        /* 反馈消息到MCM*/
        send_rsp_message(&rGetRegisterDataRsp, 
                                sizeof(rGetRegisterDataRsp), 
                                prGetRegisterDataReq->struMsgHeader.u8TransType);
}

/* 功能：设置EEPROM请求处理
 * 参数：MCM请求消息
 * 返回值：无
 * */
void set_eeprom_data_req(s8 *pskb)
{
        struct stru_set_eeprom_data_req *prSetEepromDataReq     = (struct stru_set_eeprom_data_req *)pskb;
        struct stru_set_eeprom_data_rsp rSetEepromDataRsp;
        u8 buf[2];

        /* 构造反馈消息*/
        rSetEepromDataRsp.struMsgHeader.u16MsgType              = O_MAINMCM_SET_EEPROM_DATA_RSP;
        rSetEepromDataRsp.struMsgHeader.u16MsgLength            = sizeof(rSetEepromDataRsp)
                                                                        - sizeof(rSetEepromDataRsp.struMsgHeader);
        rSetEepromDataRsp.struMsgHeader.u8TransType             = prSetEepromDataReq->struMsgHeader.u8TransType;

        buf[0]  = prSetEepromDataReq->u16Offset;
        buf[1]  = prSetEepromDataReq->u8EepromData[0];

        if (write(eepromfd, buf, 2) < 0)
            rSetEepromDataRsp.bSuccessful = SYS_ERROR;
        else
            rSetEepromDataRsp.bSuccessful = SYS_OK;

        /* 反馈消息到MCM*/
        send_rsp_message(&rSetEepromDataRsp, 
                                sizeof(rSetEepromDataRsp), 
                                prSetEepromDataReq->struMsgHeader.u8TransType);
}

/* 功能：查询寄存器请求处理
 * 参数：MCM请求消息
 * 返回值：无
 */
void get_eeprom_data_req(s8 *pskb)
{
        struct stru_get_eeprom_data_req *prGetEepromDataReq     = (struct stru_get_eeprom_data_req *)pskb;
        struct stru_get_eeprom_data_rsp rGetEepromDataRsp;
        u8 buf[1];

        /* 构造消息*/
        rGetEepromDataRsp.struMsgHeader.u16MsgType              = O_MAINMCM_GET_EEPROM_DATA_RSP;
        rGetEepromDataRsp.struMsgHeader.u16MsgLength            = sizeof(rGetEepromDataRsp) 
                                                                        - sizeof(rGetEepromDataRsp.struMsgHeader);
        rGetEepromDataRsp.struMsgHeader.u8TransType             = prGetEepromDataReq->struMsgHeader.u8TransType;

        buf[0]  =   prGetEepromDataReq->u16Offset;

        if(read(eepromfd, buf, 1) < 0)  {
                ERROR("read eeprom data error!\n");
        }
       
        rGetEepromDataRsp.u8EepromData[0]   =   buf[0];

        /* 反馈消息到MCM*/
        send_rsp_message(&rGetEepromDataRsp, 
                                sizeof(rGetEepromDataRsp), 
                                prGetEepromDataReq->struMsgHeader.u8TransType);
}

/* 功能：软件更新
 * 参数：同上
 * 返回值：无
 * */
void software_update_req(s8 *pskb)
{
        int fd;
        int ssize;

        struct stru_software_update_req  *prSoftWareUpdateReq   = (struct stru_software_update_req *)pskb; 
        struct stru_software_update_rsp  rSoftWareUpdateRsp;

        /* 消息处理*/
        rSoftWareUpdateRsp.struMsgHeader.u16MsgType             = O_MAINMCM_SOFTWARE_UPDATE_RSP;
        rSoftWareUpdateRsp.struMsgHeader.u16MsgLength           = sizeof(rSoftWareUpdateRsp) 
                                                                        - sizeof(rSoftWareUpdateRsp.struMsgHeader);
        rSoftWareUpdateRsp.struMsgHeader.u8TransType            = prSoftWareUpdateReq->struMsgHeader.u8TransType;

        fd = open(prSoftWareUpdateReq->u8FileName, O_CREAT | O_WRONLY | O_APPEND, 0644); 
        if (fd < 0) {
                ERROR("open %s file error\n", prSoftWareUpdateReq->u8FileName);
                rSoftWareUpdateRsp.bSuccessful          =       SYS_ERROR;
        } else { 
                ssize = write(fd, prSoftWareUpdateReq->u8Buffer, prSoftWareUpdateReq->u32Len); 
                if (ssize < 0) {
                        ERROR("write %s file error\n", prSoftWareUpdateReq->u8FileName);
                        rSoftWareUpdateRsp.bSuccessful          =       SYS_ERROR;
                } else
                        rSoftWareUpdateRsp.bSuccessful          =       SYS_OK;
                close(fd);
        }
        
        /* 反馈消息到MCM*/
        send_rsp_message(&rSoftWareUpdateRsp, 
                                sizeof(rSoftWareUpdateRsp), 
                                prSoftWareUpdateReq->struMsgHeader.u8TransType);
}

/* 功能：发送短信息请求处理
 * 参数：MCM请求消息
 * 返回值：无
 * */
void send_gprs_message_req(s8 *pskb)
{
        struct stru_send_gprs_message_req *prSendGprsMessageReq = (struct stru_send_gprs_message_req *)pskb;
        struct stru_send_gprs_message_rsp rSendGprsMessageRsp;

        /* 构造消息*/
        rSendGprsMessageRsp.struMsgHeader.u16MsgType            = O_MAINMCM_MODEM_RSP;
        rSendGprsMessageRsp.struMsgHeader.u16MsgLength          = sizeof(rSendGprsMessageRsp)
                                                                        - sizeof(rSendGprsMessageRsp.struMsgHeader);
        rSendGprsMessageRsp.struMsgHeader.u8TransType           = prSendGprsMessageReq->struMsgHeader.u8TransType;    
        rSendGprsMessageRsp.bSuccessful = send_gprs_message(prSendGprsMessageReq->u8PhoneNum, 
                                                        prSendGprsMessageReq->u8MessageInfo);
        /* 反馈消息到MCM*/
        send_rsp_message(&rSendGprsMessageRsp, 
                                sizeof(rSendGprsMessageRsp), 
                                prSendGprsMessageReq->struMsgHeader.u8TransType);
}

/* 功能：上位机发送zigbee信息
 * 参数：MCM请求消息
 * 返回值:无
 * */
void send_zigbee_message_req(s8 *pskb)
{
        struct stru_send_zigbee_message_req *prSendZigbeeMessageReq = (struct stru_send_zigbee_message_req *)pskb;
        struct stru_send_zigbee_message_rsp rSendZigbeeMessageRsp;

        /* 消息处理*/
        rSendZigbeeMessageRsp.struMsgHeader.u16MsgType          = O_MAINMCM_ZIGBEE_RSP;
        rSendZigbeeMessageRsp.struMsgHeader.u16MsgLength        = sizeof(rSendZigbeeMessageRsp)
                                                                        - sizeof(rSendZigbeeMessageRsp.struMsgHeader);
        rSendZigbeeMessageRsp.struMsgHeader.u8TransType         = prSendZigbeeMessageReq->struMsgHeader.u8TransType;

       rSendZigbeeMessageRsp.bSuccessful = send_zigbee_message(prSendZigbeeMessageReq->u8MessageInfo);
        
       /* 反馈消息到MCM*/
        send_rsp_message(&rSendZigbeeMessageRsp, 
                                sizeof(rSendZigbeeMessageRsp), 
                                prSendZigbeeMessageReq->struMsgHeader.u8TransType);
}

/* 功能:报警器控制
 * 参数：MCM请求消息
 * 返回值：无
 * */
void beep_control_req(s8 *pskb)
{
        struct stru_beep_control_req    *prBeepCtrlReq  = (struct stru_beep_control_req *)pskb; 
        struct stru_beep_control_rsp    rBeepCtrlRsp;

        /* 消息处理*/
        rBeepCtrlRsp.struMsgHeader.u16MsgType           = O_MAINMCM_BEEP_RSP;
        rBeepCtrlRsp.struMsgHeader.u16MsgLength         = sizeof(rBeepCtrlRsp)
                                                                - sizeof(rBeepCtrlRsp.struMsgHeader);
        rBeepCtrlRsp.struMsgHeader.u8TransType          = prBeepCtrlReq->struMsgHeader.u8TransType;

        if(prBeepCtrlReq->u8BeepCtrlOperation == 1) { //打开
                rBeepCtrlRsp.bSuccessful = start_alarm();
        } else {        //关闭
                rBeepCtrlRsp.bSuccessful = stop_alarm();
        }

        send_rsp_message(&rBeepCtrlRsp, 
                                sizeof(rBeepCtrlRsp), 
                                prBeepCtrlReq->struMsgHeader.u8TransType);
}

/* 功能:LED控制
 * 参数：MCM请求消息
 * 返回值：无
 * */
void led_control_req(s8 *pskb)
{

        struct stru_led_control_req *prLedCtrlReq       = (struct stru_led_control_req *)pskb;
        struct stru_led_control_rsp rLedCtrlRsp;
        
        /* 消息处理*/
        rLedCtrlRsp.struMsgHeader.u16MsgType            = O_MAINMCM_LED_RSP;
        rLedCtrlRsp.struMsgHeader.u16MsgLength          = sizeof(rLedCtrlRsp) - sizeof(rLedCtrlRsp.struMsgHeader);
        rLedCtrlRsp.struMsgHeader.u8TransType          = prLedCtrlReq->struMsgHeader.u8TransType;
        if (prLedCtrlReq->u8LedCmd == 1) {
                rLedCtrlRsp.bSuccessful = flash_led(prLedCtrlReq->u32BlinkTime);
        } else {
                rLedCtrlRsp.bSuccessful = stop_led();
        }
        
        /* 反馈消息到MCM*/
        send_rsp_message(&rLedCtrlRsp, 
                                sizeof(rLedCtrlRsp), 
                                prLedCtrlReq->struMsgHeader.u8TransType);
}

/* 功能:硬件自检
 * 参数：同上
 * 返回值:无
 * */
void hardware_selftest_req(s8 *pskb)
{
        struct stru_selftest_rsp rSelfTestRsp;
        struct stru_selftest_req *prSelfTestReq = (struct stru_selftest_req *)pskb;

        /* 构造消息*/
        rSelfTestRsp.struMsgHeader.u16MsgType   = O_MAINMCM_HARDWARE_SELFTEST_RSP;
        rSelfTestRsp.struMsgHeader.u16MsgLength = sizeof(rSelfTestRsp)
                                                        - sizeof(rSelfTestRsp.struMsgHeader);
        rSelfTestRsp.struMsgHeader.u8TransType  = prSelfTestReq->struMsgHeader.u8TransType;
        rSelfTestRsp.s32SelfTestResult  = 0 /* 添加硬件自检处理模块 hardware_selftest()*/;

        /* 反馈消息到MCM*/
        send_rsp_message(&rSelfTestRsp, 
                                sizeof(rSelfTestRsp), 
                                prSelfTestReq->struMsgHeader.u8TransType);
}

/* 功能：时间校准
 * 参数：同上
 * 返回值：无
 * */
void time_adjust_req(s8 *pskb)
{
        struct tm tm;
        time_t  tt;
        struct timeval tv;

        struct stru_tod_adjust_req      *prTodAdjustReq      = (struct stru_tod_adjust_req *)pskb;
        struct stru_tod_adjust_rsp      rTodAdjustRsp;  
        
        /* 构造消息*/
        rTodAdjustRsp.struMsgHeader.u16MsgType          = O_MAINMCM_TOD_ADJUST_RSP;
        rTodAdjustRsp.struMsgHeader.u16MsgLength        = sizeof(rTodAdjustRsp)
                                                                - sizeof(rTodAdjustRsp.struMsgHeader);
        rTodAdjustRsp.struMsgHeader.u8TransType         = prTodAdjustReq->struMsgHeader.u8TransType;

        tm.tm_sec  = prTodAdjustReq->struTimeInfo.u8Second;
        tm.tm_min  = prTodAdjustReq->struTimeInfo.u8Minute;
        tm.tm_hour = prTodAdjustReq->struTimeInfo.u8Hour;
        tm.tm_mday = prTodAdjustReq->struTimeInfo.u8Day;
        tm.tm_mon  = prTodAdjustReq->struTimeInfo.u16Month - 1; //[0:11]
        tm.tm_year = prTodAdjustReq->struTimeInfo.u16Year - 1900;
        printf("month = %d\n", tm.tm_mon);
        tt = mktime(&tm);
        if (tt == -1) { 
                rTodAdjustRsp.bSuccessful = SYS_ERROR;
        } else {
                tv.tv_sec = (long)tt;
                tv.tv_usec = 0;
                rTodAdjustRsp.bSuccessful = settimeofday(&tv,NULL);
                system("hwclock");
        }
        /* 反馈消息到MCM*/
        send_rsp_message(&rTodAdjustRsp, 
                                sizeof(rTodAdjustRsp), 
                                prTodAdjustReq->struMsgHeader.u8TransType);
}
