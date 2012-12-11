#ifndef __DEVICE_H
#define __DEVICE_H

#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include "common.h"
#include "msg.h"
#define READ        1
#define WRITE       0

#define TRANSFER_NET    0
#define TRANSFER_UART   1

/* 设备操作命令字*/

#define LED1_ON		        (0x10001)
#define LED1_OFF	        (0x10002)
#define LED2_ON		        (0x10003)
#define LED2_OFF	        (0X10004)

#define	REGEDITOR_WRITE	        (0x10005)
#define REGEDITOR_READ	        (0x10006)

#define BEEP_ON                (0x10007)
#define BEEP_OFF               (0x10008)


#define IOCTL_DS18B20_S_RESET                   0x10009
#define IOCTL_DS18B20_S_START                   0x10010
#define IOCTL_DS18B20_S_BIT                     0x10011

#define ADC_RESOL               (0x10012)
#define ADC_INPUT_PIN           (0x10013)

#define EEPROM_READ_DATA        (0x10008)
#define EEPROM_WRITE_DATA       (0x10009)
#define EEPROM_WRITE_ADDR       (0x10010)

/* 设备名称*/
#define REGEDITOR_DEV           "/dev/regeditor"
#define LED_DEV                 "/dev/leds"
#define BEEP_DEV                "/dev/beeps"
#define TEMP_DEV                "/dev/ds18b20"
#define ADC_DEV                 "/dev/adc"

#define BUTTON_DEV              "/dev/event1"
#define EEPROM_DEV              "/dev/at24cxx0"
#define LCD_DEV                 "/dev/fb0"
#define GPRS_DEV                "/dev/s3c2410_serial0"
#define ZIGBEE_DEV              "/dev/s3c2410_serial1"

/* 温度报警阀值*/
#define TEMPERATURE_ALARM       35

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
extern void get_ds18b20_temperature(f32 *TempInfo);

/* 读电压值*/
extern void get_adc_voltage(f32 *AdcInfo);

/* 配置 ADC*/
extern void adc_config(int bit, int channel);

/* 获取红外，按键:
 * 返回值: true:异常; false:正常
 * */
extern bool get_button_key(void);

#endif
