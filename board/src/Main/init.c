#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include "linux/input.h"
#include "log.h"
#include "device.h"
#include "msg.h"
#include "socket.h"

/* 功能：打开设备
 * 返回值：-1:失败; 0:成功
 * 参数：无
 * */
int init_device(void)
{
        int arg = 12;

        regeditorfd = open(REGEDITOR_DEV, O_RDWR);
        if(regeditorfd < 0) {
            ERROR("open regeditor device error\n");
            return -1;
        }
        
        ledfd = open(LED_DEV, O_RDWR);
        if(ledfd < 0) {
            ERROR("open led device error\n");
            return -1;
        }
        
        beepfd = open(BEEP_DEV, O_RDWR);
        if (beepfd < 0) {
            ERROR("open beep device error\n");
            return -1;
        }
        
        tempfd = open(TEMP_DEV, O_RDWR);
        if (tempfd < 0) {
            ERROR("open temperature device error\n");
            return -1;
        }

        adcfd = open(ADC_DEV, O_RDWR);
        if (adcfd < 0) {
            ERROR("open adc device error\n");
            return -1;
        }

        buttonfd = open(BUTTON_DEV, O_RDWR);
        if (buttonfd < 0) {
            ERROR("open button device error\n");
            return -1;
        }
        
        eepromfd = open(EEPROM_DEV, O_RDWR);
        if (eepromfd < 0) {
            ERROR("open eeprom device error\n");
            return -1;
        }
        
        zigbeefd = open(ZIGBEE_DEV, O_RDWR);
        if (zigbeefd < 0) {
            ERROR("open zigbee device error\n");
            return -1;
        }
        
        setBps(zigbeefd,115200);
        
        if(setOption(zigbeefd,8,1,'N')==-1)
        {
                printf("Set Option Error\n");
                return -1;
        }
        
        /* 配置温度传感器*/
        ioctl(tempfd, IOCTL_DS18B20_S_BIT, &arg);

        /* 配置ADC*/
        adc_config(10, 1);
        return 0;
}

/* 功能：配置GPRS短信服务中心
 * 返回值：1:失败；0：成功
 * 参数：无
 * */
int gprs_config(void)
{
    char *cmd[] = {"AT+CMFG=1\r",
                    "AT+CSCA=\"+8613800100500\"\r"};
    int i;

    for (i = 0; i < sizeof(cmd) / sizeof(cmd[0]); i++) {
        write(gprsfd, cmd[i], strlen(cmd[i]));
    }
    return 0;
}

/* 功能：发送短信息内容
 * 返回值：-1:失败；0：成功
 * 参数1：手机号码
 * 参数2：短信息内容
 * */
#define MSG_LEN     512
int send_gprs_message(char *telephone, char *msg)
{
    char cmd_buf[23];
    char msg_buf[512];
    int len = strlen(msg);

    bzero(cmd_buf, sizeof(cmd_buf));
    bzero(msg_buf, sizeof(msg_buf));

    /* 指定对方手机号*/
    strcpy(cmd_buf, "AT+CMGS=\"");
    strcpy(cmd_buf, telephone);
    strcat(cmd_buf, "\"\r");

    write(gprsfd, cmd_buf, strlen(cmd_buf));

    /* 构造短信内容*/
    strcpy(msg_buf, msg);
    msg_buf[len] = 0x1A;
    msg_buf[len+1] = '\r';
    msg_buf[len+2] = '\0';
    
    write(gprsfd, msg_buf, strlen(msg_buf));

    return 0;
}

int send_zigbee_message(char *msg)
{
        return 0;
}

/* 功能：打开报警器
 * 返回值：无
 * 参数  ： 无
 * */
int start_alarm(void)
{
    return ioctl(beepfd, BEEP_ON);
}

/* 功能：关闭报警器
 * 返回值：无
 * 参数：无
 * */
int stop_alarm(void)
{
    return ioctl(beepfd, BEEP_OFF);
}

/* 功能：打开灯
 * 返回值：无
 * 参数：无
 * */
int flash_led(unsigned long time)
{
    return ioctl(ledfd, LED1_ON);
}

/* 功能：关闭灯
 * 返回值：无
 * 参数：无
 * */
s32 stop_led(void)
{
    return ioctl(ledfd, LED1_OFF);
}

/* 功能：获取温度值
 * 返回值：温度值
 * 参数：无
 * */
void get_ds18b20_temperature(f32 *TempInfo)
{
    u32 data;
    s8  tmp[10];

    memset(tmp, 0, sizeof(tmp));
    read(tempfd, &data, sizeof(data));
    *TempInfo = (f32)data / 100;
    sprintf(tmp, "%.1f", *TempInfo);
    *TempInfo = atof(tmp);
}

/* 功能：配置ADC参数
 * 返回值：无
 * 参数：转换精度，通道
 * */
static int adcbit;
static int adcchannel;
void adc_config(int bit, int channel)
{
    adcbit = bit;
    adcchannel = channel;
    
    ioctl(adcfd, ADC_RESOL, &adcbit);
    ioctl(adcfd, ADC_INPUT_PIN, &adcchannel);
}

/* 功能：获取电压值
 * 返回值：电压值
 * 参数：无
 * */
void get_adc_voltage(f32 *AdcInfo)
{
    u32 voltage;
    s8  tmp[10];

    memset(tmp, 0, sizeof(tmp));
    read(adcfd, &voltage, sizeof(voltage));
    *AdcInfo =  (float)voltage / (1 << adcbit) * 3.3;
    sprintf(tmp, "%.1f", *AdcInfo);
    *AdcInfo = atof(tmp);
}

/* 功能：获取按键或者红外
 * 返回值：true：异常
 * 参数：无
 * */
bool get_button_key(void)
{
    struct input_event button;
    
    read(buttonfd, &button, sizeof(button));
    if(button.type == EV_KEY) {
        if(button.code == KEY_DOWN) {
            return true;
        }
    }
}

/* 功能：系统重启
 * 返回值：无
 * 参数：无
 * */
void system_reboot(void)
{
    char *cmd = "reboot";
    system(cmd);
}

/* 功能：发送反馈消息给ＭＣＭ
 * 参数：message:消息指针;len：消息长度; TransType:传输类型
 * 返回值：无
 * */
void send_rsp_message(void *message, u32 len, u8 TransType)
{
        if (TransType == TRANSFER_NET) {
                if(sendto(server_sockfd, message, len, 0, 
                                        (struct sockaddr *)&client_addr, sin_size) < 0) {
                        ERROR("send net packet error\n");
                }
        } else if (TransType == TRANSFER_UART) {
                if(write(zigbeefd, message, len) < 0) {
                        printf("send rsp message error\n");
                }
        }
}
