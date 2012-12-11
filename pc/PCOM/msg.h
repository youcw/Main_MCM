#ifndef MSG_H
#define MSG_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define READ    1
#define WRITE   0

#define SYS_OK      0
#define SYS_ERROR   1

#define TRANSFER_NET    0
#define TRANSFER_UART   1

/* 消息号*/
/* MCM<->Main 1 ~ 100*/
#define O_MCMMAIN_MACHINE_INFO_QUERY_REQ            1   /* 查看系统信息*/
#define O_MCMMAIN_SET_REGISTER_DATA_REQ             2   /* 设置寄存器*/
#define O_MCMMAIN_GET_REGISTER_DATA_REQ             3   /* 获取寄存器*/
#define O_MCMMAIN_SET_EEPROM_DATA_REQ               4   /* 设置作EEPROM*/
#define O_MCMMAIN_GET_EEPROM_DATA_REQ               5   /* 获取EEPROM*/
#define O_MCMMAIN_SOFTWARE_UPDATE_REQ               6   /* 软件在线升级*/
#define O_MCMMAIN_MODEM_REQ                         7   /* 操作3G Modem*/
#define O_MCMMAIN_ZIGBEE_REQ                        8   /* 操作ZIGBEE*/
#define O_MCMMAIN_BEEP_REQ                          9   /* 操作蜂鸣器*/
#define O_MCMMAIN_LED_REQ                           10  /* 操作LED*/
#define O_MCMMAIN_HARDWARE_SELFTEST_REQ             11  /* 硬件自检*/
#define O_MCMMAIN_TOD_ADJUST_REQ                    12  /* 时间校准*/
#define O_MCMMAIN_VERSION_QUERY_REQ                 13  /* 查看版本信息*/

/* Main<->MCM 101 ~ 150*/
#define O_MAINMCM_MACHINE_INFO_QUERY_RSP            101  /* 查看系统信息*/
#define O_MAINMCM_SET_REGISTER_DATA_RSP             102  /* 设置寄存器*/
#define O_MAINMCM_GET_REGISTER_DATA_RSP             103  /* 获取寄存器*/
#define O_MAINMCM_SET_EEPROM_DATA_RSP               104  /*设置作EEPROM*/
#define O_MAINMCM_GET_EEPROM_DATA_RSP               105  /* 获取EEPROM*/
#define O_MAINMCM_SOFTWARE_UPDATE_RSP               106  /* 软件在线升级*/
#define O_MAINMCM_MODEM_RSP                         107  /* 操作3G Modem*/
#define O_MAINMCM_ZIGBEE_RSP                        108  /* 操作ZIGBEE*/
#define O_MAINMCM_BEEP_RSP                          109  /* 操作蜂鸣器*/
#define O_MAINMCM_LED_RSP                           110  /* 操作LED*/
#define O_MAINMCM_HARDWARE_SELFTEST_RSP             111  /* 硬件自检*/
#define O_MAINMCM_TOD_ADJUST_RSP                    112  /* 时间校准*/
#define O_MAINMCM_VERSION_QUERY_RSP                 113  /* 查看版本信息*/

/* Main->WebServer 151 ~ 200 */
#define O_MAINWEB_GET_TEMP_QUERY_RSP                151  /* 获取温度*/
#define O_MAINWEB_GET_PIC_QUERY_RSP                 152  /*获取图片*/
#define O_MAINWEB_GET_VIDEO_QUERY_RSP               153  /*获取视频 */
#define O_MAINWEB_BEEP_RSP                          154  /* 操作蜂鸣器*/
#define O_MAINWEB_WATERHEATER_RSP                   155  /* 操作热水器*/
#define O_MAINWEB_INFRARED_RSP                      156  /* 操作红外*/

/* WebServer->Main 201 ~ 300*/
#define O_WEBMAIN_GET_TEMP_QUERY_REQ                201  /* 获取温度*/
#define O_WEBMAIN_GET_PIC_QUERY_REQ                 202  /*获取图片*/
#define O_WEBMAIN_GET_VIDEO_QUERY_REQ               203  /*获取视频 */
#define O_WEBMAIN_BEEP_REQ                          204  /* 操作蜂鸣器*/
#define O_WEBMAIN_WATERHEATER_REQ                   205  /* 操作热水器*/
#define O_WEBMAIN_INFRARED_REQ                      206  /* 操作红外*/

typedef char                s8;
typedef unsigned char       u8;
typedef signed short        s16;
typedef unsigned short      u16;
typedef int                 s32;
typedef unsigned    int     u32;
typedef float               f32;
typedef signed long long    s64;
typedef unsigned long long  u64;

#define BUF_SIZE                                (5 * 1024)

/* 消息头 */
typedef struct {
    u16     u16MsgType;         /* 消息类型*/
    u16     u16MsgLength;       /*有效消息数据长度*/
    u8      u8TransType;
    u8      u8Reserved[3];
}STRU_MSG_HEAD;

/* 时间信息*/
typedef struct {
    u16     u16Year;
    u16     u16Month;
    u8      u8Day;
    u8      u8Hour;
    u8      u8Minute;
    u8      u8Second;
}STRU_TIME_INFO;

/* MCM->Main 查询系统信息*/
struct  stru_machine_info_req {
    STRU_MSG_HEAD   struMsgHeader;
};

/* Main->MCM 反馈系统信息*/
struct stru_machine_info_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    f32             f32Temp;
    f32             f32Vol;
    f32             f32CpuFreq;
    u32             u32FreeMem;
    u32             u32FreeDisk;
};

/* MCM向Main设置寄存器中的数据*/
struct stru_set_register_data_req {
    STRU_MSG_HEAD   struMsgHeader;
    u32             u32Offset;
    u32             u32RegisterData;
};

/* Main向MCM返回寄存器配置结果 */
struct stru_set_register_data_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main查询寄存器数据 */
struct stru_get_register_data_req {
    STRU_MSG_HEAD   struMsgHeader;
    u32             u32Offset;
};

/* Main向MCM返回寄存器数据 */
struct stru_get_register_data_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u32             u32RegisterData;
};

/* MCM向Main设置EEPROM中的数据 */
struct stru_set_eeprom_data_req {
    STRU_MSG_HEAD   struMsgHeader;
    u16             u16Offset;
    u16             u16Reserved;
    u8              u8EepromData[4];
};

/* Main向MCM返回配置结果*/
struct stru_set_eeprom_data_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main查询EEPROM中的数据 */
struct stru_get_eeprom_data_req {
    STRU_MSG_HEAD   struMsgHeader;
    u16             u16Offset;
    u16             u16Reserved;
};

/* Main向MCM返回EEPROM中的数据*/
struct stru_get_eeprom_data_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              u8EepromData[4];
};

/* MCM向Main发送软件升级请求 */
struct stru_software_update_req {
    STRU_MSG_HEAD   struMsgHeader;
    s8              s8FileName[20];
    u32             u32Len;
    u8              u8Buffer[BUF_SIZE];
};

/* Main向MCM返回软件升级结果 */
struct stru_software_update_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main请求发送短信息*/
struct stru_send_gprs_message_req {
    STRU_MSG_HEAD   struMsgHeader;
    s8              s8PhoneNum[11];
    s8              s8Reserved;
    s8              s8MessageInfo[20];
};

/* Main向MCM返回短信息发送结果 */
struct stru_send_gprs_message_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main请求发送ZIGBEE控制信息*/
struct stru_send_zigbee_message_req {
    STRU_MSG_HEAD   struMsgHeader;
    s8              s8MessageInfo[20];
};

/* Main向MCM返回操作结果 */
struct stru_send_zigbee_message_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main发送控制蜂鸣器请求 */
struct stru_beep_control_req {
    STRU_MSG_HEAD   struMsgHeader;
    u8              u8BeepCtrlOperation;
    u8              u8Reserved[3];
};

/* Main向Main返回配置结果 */
struct stru_beep_control_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main发送控制LED请求 */
struct stru_led_control_req {
    STRU_MSG_HEAD   struMsgHeader;
    u8              u8LedType;
    u8              u8LedCmd;
    u8              u8Reserved[2];
    u32             u32BlinkTime;
};

/* Main向Main返回配置结果*/
struct stru_led_control_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main发送自检请求*/
struct stru_selftest_req {
    STRU_MSG_HEAD   struMsgHeader;
};

/* Main返回设备自检结果 */
struct stru_selftest_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    s32             s32SelfTestResult;
};

/* MCM向Main发送时间配置请求 */
struct stru_tod_adjust_req {
    STRU_MSG_HEAD   struMsgHeader;
    STRU_TIME_INFO  struTimeInfo;
};

/* Main向MCM返回时间配置结果 */
struct stru_tod_adjust_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              bSuccessful;
    u8              u8Reserved[3];
};

/* MCM向Main发送获取软件版本请求 */
struct stru_get_version_req {
    STRU_MSG_HEAD   struMsgHeader;
    u8              u8QueryId;
    u8              u8Reserved[3];
};

/* Main返回软件版本号*/
struct stru_get_version_rsp {
    STRU_MSG_HEAD   struMsgHeader;
    u8              u8QueryId;
    u8              u8Padding[3];
    s8              s8Version[8];
};

#endif // MSG_H
