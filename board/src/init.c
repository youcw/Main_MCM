#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include "linux/input.h"
#include "log.h"
#include "device.h"

/* 功能：打开设备
 * 返回值：-1:失败; 0:成功
 * 参数：无
 * */
int init_device(void)
{
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

        lcdfd = open(LCD_DEV, O_RDWR);
        if (lcdfd < 0) {
            ERROR("open lcd device error\n");
            return -1;
        }

        gprsfd = open(GPRS_DEV, O_RDWR);
        if (gprsfd < 0) {
            ERROR("open gprs device error\n");
            return -1;
        }

        zigbeefd = open(ZIGBEE_DEV, O_RDWR);
        if (zigbeefd < 0) {
            ERROR("open zigbee device error\n");
            return -1;
        }

        beepfd = open(BEEP_DEV, O_RDWR);
        if (beepfd < 0) {
            ERROR("open beep device error\n");
            return -1;
        }
        
        if (init_uart(gprsfd, B115200) == -1) {
            ERROR("init uart for gprs error\n");
            return -1;
        }
        
        if (init_uart(zigbeefd, B115200) == -1) {
            ERROR("init uart for zigbee error\n");
            return -1;
        }
        
        if (gprs_config() == -1) {
            ERROR("config gprs center error\n");
            return -1;
        }
        
        return 0;
}

/* 功能：初始化串口 
 * 返回值：0：成功；1：失败 
 * 参数fd：串口文件描述符，即那个串口
 * 参数speed:波特率
 * */
int init_uart(int fd, int speed)
{
    struct termios   options;

    bzero(&options, sizeof(options));
    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    options.c_cflag |= (CS8 | CREAD);
    options.c_iflag |= IGNPAR;

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options); 

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

/* 功能：打开报警器
 * 返回值：无
 * 参数  ： 无
 * */
int start_alarm(void)
{
    return ioctl(beepfd, ALARM_ON);
}

/* 功能：关闭报警器
 * 返回值：无
 * 参数：无
 * */
int stop_alarm(void)
{
    return ioctl(beepfd, ALARM_OFF);
}

/* 功能：打开灯
 * 返回值：无
 * 参数：无
 * */
void flash_led(void)
{
    ioctl(ledfd, LED_ON);
}

/* 功能：关闭灯
 * 返回值：无
 * 参数：无
 * */
void stop_led(void)
{
    ioctl(ledfd, LED_OFF);
}

/* 功能：获取温度值
 * 返回值：温度值
 * 参数：无
 * */
float get_ds18b20_temperature(void)
{
    unsigned int temp;

    read(tempfd, &temp, sizeof(temp));

    return (float)temp / 4096 * 100;
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
    
    ioctl(adcfd, ADC_INPUT_BIT, adcbit);
    ioctl(adcfd, ADC_INPUT_PIN, adcchannel);
}

/* 功能：获取电压值
 * 返回值：电压值
 * 参数：无
 * */
float get_adc_voltage(void)
{
    unsigned int voltage;

    read(adcfd, &voltage, sizeof(voltage));

    return (float)voltage / (1 << adcbit) * 3.3;
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
        if(button.code == KEY_6) {
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
