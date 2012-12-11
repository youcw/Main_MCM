#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include <termios.h>

/** 主程序端调试开关 */
#define GPRS_MAIN_DEBUG 1
/** WEB端调试开关*/
#define GPRS_WEB_DEBUG 0

/** ftok所使用的路径*/
#define MSG_PATH        "/var"
#define MSG_PROJ_ID     'b'

/** ftok所使用的编号*/
#define M_REQUEST       (1000) 
#define M_RESPONSE      (1001)

/** 请求/响应消息队列的id*/
int req_id;
int rsp_id;

pthread_t       thread_temperature;
pthread_t       thread_infrared;
pthread_t       thread_adc;
pthread_t       thread_led;

extern int  create_socket(void);
extern void *thread_monitor_temperature(void *pdata);
extern void *thread_monitor_infrared(void *pdata);
extern void *thread_monitor_adc(void *pdata);
extern void *thread_monitor_led(void *pdata);

/** 获得请求队列/响应队列*/
int get_que_req (void);
int get_que_rsp (void);


/* ##########################################
 * 以下为web 模块用到的宏和结构体和函数
 * ##########################################
 */
/* ##########################################
 * 以下为WebServer->Main的宏
 * ##########################################
 */

/* WebServer->Main 200 ~ 206 */
#define O_WEBMAIN_GET_TEMP_QUERY_REQ        201  /* 获取温度*/
#define O_WEBMAIN_GET_PIC_QUERY_REQ         202  /* 获取图片*/
#define O_WEBMAIN_GET_VIDEO_QUERY_REQ       203  /* 获取视频 */
#define O_WEBMAIN_BEEP_REQ                  204  /* 操作蜂鸣器*/
#define O_WEBMAIN_WATERHEATER_REQ           205  /* 操作热水器*/
#define O_WEBMAIN_INFRARED_REQ              206  /* 操作红外*/

/* Main->WebServer 151 ~ 200 */
#define O_MAINWEB_GET_TEMP_QUERY_RSP        151  /* 获取温度*/
#define O_MAINWEB_GET_PIC_QUERY_RSP         152  /* 获取图片*/
#define O_MAINWEB_GET_VIDEO_QUERY_RSP       153  /* 获取视频 */
#define O_MAINWEB_BEEP_RSP                  154  /* 操作蜂鸣器*/
#define O_MAINWEB_WATERHEATER_RSP           155  /* 操作热水器*/
#define O_MAINWEB_INFRARED_RSP              156  /* 操作红外*/

#define PIC_PATH_LENGTH_MAX 1024    /*图片路径的最大长度*/
#define MSG_BUF_LENGTH 2048     /*消息队列缓冲区的长度*/
/* ##########################################
 * 以下为webServer<->的结构体
 * ##########################################
 */

typedef struct header {
    long MsgType;
    unsigned long MsgLength;
}STRU_MSG_HEADER;

struct stru_req { /* WebServer->Main任意请求的结构体 */
    STRU_MSG_HEADER struMsgHeader; /*请求温度的消息头*/
    char mtext[MSG_BUF_LENGTH]; /*请求时携带的参数*/
};

struct stru_temp_rsp {/* Main->WebServer返回温度的结构体 */
    long struMsgHeader; /*响应温度请求的消息头*/
    float f32Temp; /*返回的温度值，32位float型*/
};

struct stru_pic_rsp {/* Main->WebServer返回图片信息的结构体*/
    long struMsgHeader; /*响应图片请求的消息头*/
    char cpPicPath[PIC_PATH_LENGTH_MAX]; /*图片的路径*/
};

struct stru_beep_rsp {  /* Main->WebServer返回的蜂鸣器信息*/
    long struMsgHeader; /* 响应蜂鸣器开关的消息头*/
    int currentState;   /* 目前蜂鸣器的状态 */
};

struct stru_waterheater_rsp {   /* Main->WebServer返回热水器信息*/
    long struMsgHeader;         /* 响应热水器的消息头 */
    int currentState;           /* 目前热水器的目前的状态 */
};

/**
* 获得cgi的数据
* 返回值：返回从浏览器获得的数据，发生错误则返回NULL
* 参数：
*      fp:从fp流中读取数据(一般fp为stdin)
*      requestmethod:请求的方法(get和post两种)
*/
char *
getcgidata (FILE * fp, char *requestmethod);

/**
 * 获得key指定的数据
 * 参数:
 *      input : 要解析的键值对
 *      key : 键
 *      value : 返回的值
 */
void
getcgivalue (char *input, char *key, char *value);
typedef enum __bool {false=0, true=1}bool;

#endif
