#ifndef __DEVICE_H
#define __DEVICE_H

#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include "common.h"
#define READ        1
#define WRITE       0

/* 设备操作命令字*/
#define ALARM_ON        (0x10000)
#define ALARM_OFF       (0x10001)
#define LED_ON          (0x10002)
#define LED_OFF         (0x10003)
#define ADC_INPUT_BIT   (0x10004)
#define ADC_INPUT_PIN   (0x10005)
#define REGEDITOR_READ  (0x10006)
#define REGEDITOR_WRITE (0x10007)
#define EEPROM_READ     (0x10008)
#define EEPROM_WRITE    (0x10009)

/* 设备名称*/
#define REGEDITOR_DEV   "/dev/regeditor"
#define LED_DEV         "/dev/led"
#define TEMP_DEV        "/dev/temp"
#define ADC_DEV         "/dev/adc"
#define BUTTON_DEV      "/dev/event1"
#define EEPROM_DEV      "/dev/eeprom"
#define LCD_DEV         "/dev/fb0"
#define GPRS_DEV        "/dev/s3c2410_serial0"
#define ZIGBEE_DEV      "/dev/s3c2410_serial1"
#define BEEP_DEV        "/dev/beep"

/* 温度报警阀值*/
#define TEMPERATURE_ALARM       50

/* 设备文件描述符*/
int regeditorfd;
int ledfd;
int tempfd;
int adcfd;
int buttonfd;
int eepromfd;
int lcdfd;
int gprsfd;
int zigbeefd;
int beepfd;

/* 打开设备*/
extern int init_device(void);

/* 初始化串口*/
extern int init_uart(int fd, int speed);

/* GPRS 配置*/
extern int gprs_config(void);

/* 发送GPRS 短信*/
extern int send_gprs_message(char *telephone, char *msg);

/* 开启报警器*/
extern int start_alarm(void);

/* 关闭报警器*/
extern int stop_alarm(void);

/* 闪灯*/
extern int flash_led(unsigned long time);

/* 关闭灯*/
extern int stop_led(void);

/* 读温度*/
extern float get_ds18b20_temperature(void);

/* 读电压值*/
extern float get_adc_voltage(void);

/* 配置 ADC*/
extern void adc_config(int bit, int channel);

/* 获取红外，按键:
 * 返回值: true:异常; false:正常
 * */
extern bool get_button_key(void);

#endif
