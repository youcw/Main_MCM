#ifndef MSG_H
#define MSG_H
/* 消息号*/
#define READ    1
#define WRITE   0

#define OK      1
#define ERROR   0

/* 板卡状态*/
#define PC_ARM_CHECKMACHINESTAT_REQ             (1)
#define ARM_PC_CHECKMACHINESTAT_RSP             (2)

/* 寄存器操作*/
#define PC_ARM_RegisterControl                  (3)
#define ARM_PC_RegisterControl_Rsp              (4)

/* EEPROM */
#define PC_ARM_EEPROM_Control                   (5)
#define ARM_PC_EEPROM_Control_Rsp               (6)

/* 软件更新*/
#define PC_ARM_SOFTWARE_UPDATE_REQ              (7)
#define ARM_PC_SOFTWARE_UPDATE_RSP              (8)

/* GPRS短信息*/
#define PC_ARM_SENDGPRSMESSAGE_REQ              (9)
#define ARM_PC_SENDGPRSMESSAGE_RSP              (10)

/* ZIGBEE信息*/
#define PC_ARM_SENDZIGBEEMESSAGE_REQ            (11)
#define ARM_PC_SENDZIGBEEMESSAGE_RSP            (12)

/* 报警器控制*/
#define PC_ARM_BEEPCONTROL_REQ                  (13)
#define ARM_PC_BEEPCONTROL_RSP                  (14)

/* LED控制*/
#define PC_ARM_LEDCONTROL_REQ                   (15)
#define ARM_PC_LEDCONTROL_RSP                   (16)

/* 硬件自检 */
#define PC_ARM_HARDWARE_TESTSELF_REQ            (17)
#define ARM_PC_HARDWARE_TESTSELF_RSP            (18)

/* 时间校准*/
#define PC_ARM_TIME_ADJUST_REQ                  (19)
#define ARM_PC_TIME_ADJUST_RSP                  (20)

#define BUF_SIZE                                (1024*5)
typedef struct MsgInfo Msg;

/* 消息头 */
struct MsgInfo {
        unsigned long MsgId;                    /* 消息类型*/
        unsigned long MsgLen;                   /* 消息长度，不包含消息头*/
};

/* 寄存器查看消息 */
struct RegisterControl {
        Msg             RegsMsg;                /* 消息头 */
        unsigned long   Addr;                   /* 寄存器地址*/
        unsigned long   Data;                   /* 传输数据 */
        unsigned long   flag;                   /* 1:读; 0:写*/
};

/* 软件更新消息 */
struct SoftWareUpdate {
        Msg             SoftWareUpdateMsg;      /* 消息头*/
        char            FileName[20];          /* 文件名*/
        unsigned long   Len;                    /* 传输长度*/
        char            buf[BUF_SIZE];           /* 缓冲区*/
        int             Result;                 /* 0:成功; -1:失败*/
};

/* 查询系统状态 */
struct CheckMachineStat {
        Msg             CheckMachineStatMsg;          /* 消息头*/
        unsigned long   MachineStat;                  /* 板卡状态 1:正常，0：异常*/
        float           TempData;                     /* 温度值*/
        float           Voltage;                      /* 获取电压*/
        unsigned long   CpuFreq;                      /* 当前CPU频率*/
        unsigned long   FreeMemSpace;                 /* 当前系统剩余内存*/
        unsigned long   FreeDiskSpace;                /* 当前系统剩余磁盘*/
};

/* 操作EEPROM */
struct EepromControl {
                Msg             ControlEepromMsg;       /* 消息头*/
                unsigned long   addr;                   /* 地址 */
                unsigned long   data;                   /* 数据 */
                unsigned long   flag;                   /* 1:读; 0:写*/
};

/* GPRS短信息*/
struct GprsMessage {
    Msg             GprsMessageMsg;             /* 消息头 */
    char            TelephoneNumber[12];        /* 电话号码 */
    char            Message[128];               /* 短信息 */
    int             Result;                     /* 0:成功，-1：失败*/
};

/* ZIGBEE控制命令*/
struct ZigbeeMessage {
    Msg             ZigbeeMessageMsg;           /* 消息头*/
    char            Message[128];               /* 控制命令 */
    int             Result;                 /* 0:成功， -1：失败*/
};

/* 报警器控制*/
struct BeepControl {
    Msg             BeepControlMsg;              /* 消息头*/
    unsigned long   Flag;                 /* 1=打开，0=关闭*/
    int             Result;                 /* 0:成功， -1：失败*/
};

/* LED控制*/
struct LedControl {
    Msg             LedControlMsg;              /* 消息头 */
    unsigned long   Flag;                 /* 1=打开，0=关闭*/
    unsigned long   FlashTime;            /* 闪烁时间间隔*/
    int             Result;                 /* 0:成功， -1：失败*/
};

/* 硬件自检*/
struct HardWareTestSelf {
    Msg             HardWareTestSelfMsg;
};

/* 时间校准*/
struct TimeAdjust {
    Msg                 TimeAdjustMsg;      /*消息头 */
    unsigned    short   year;
    unsigned    short   month;
    unsigned    char    day;
    unsigned    char    hour;
    unsigned    char    min;
    unsigned    char    sec;
    int                 Result;             /* 0：成功； -1：失败*/
};
#endif // MSG_H
