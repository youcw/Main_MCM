#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

#include "device.h"
#include "common.h"
#include "msg.h"
#include "log.h"
#include "socket.h"

/* 功能：建立socket，与PC进行通信，处理消息
 * 返回值：-1：失败；0：成功
 * 参数：无
 * */

#define     SIZE    (1024 * 6)

int create_socket(void)
{
        Msg msg_head;

        int server_sockfd;
        int len;
        int sin_size;
        char buf[SIZE];
        struct sockaddr_in server_addr;
        struct sockaddr_in client_addr;

        memset(&server_addr, 0, sizeof(server_addr));

        server_addr.sin_family      = AF_INET;  //设置为IP通信
        server_addr.sin_addr.s_addr = INADDR_ANY;   //无限制
        server_addr.sin_port        = htons(8000);

        if ((server_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
                ERROR("socket error\n");
                return -1;
        }

        if(bind(server_sockfd, (struct sockaddr *)&server_addr, 
                                sizeof(struct sockaddr)) < 0) {
                ERROR("bind error\n");
                return -1;
        }

        sin_size = sizeof(struct sockaddr_in);

        INFO("waiting for packet......\n");

        bzero(buf, SIZE);
        
        for(;;) {
                /* 接收消息*/
                if((len = recvfrom(server_sockfd, buf, SIZE, 0, 
                                                (struct sockaddr*)&client_addr, &sin_size)) < 0) {
                        ERROR("receive packet error\n");
                        return -1;
                }
                INFO("received packet from %s\n",inet_ntoa(client_addr.sin_addr));

                /* 消息处理
                 * 解析消息头
                 * 分发消息
                 * */
                memcpy(&msg_head, buf, sizeof(msg_head));
                switch(msg_head.MsgId) {
                        /* 板卡状态*/
                        case PC_ARM_CHECK_MACHINE_STAT_REQ:
                                get_machine_stat(buf);
                                break;

                                /* 寄存器操作请求*/
                        case PC_ARM_REGISTER_RW_REQ:
                                register_xfer(buf);
                                break;

                                /* 软件更新 */
                        case PC_ARM_SOFTWARE_UPDATE_REQ:
                                sw_update(buf);
                                break;

                                /* EEPROM */
                        case PC_ARM_EEPROM_RW_REQ:
                                eeprom_xfer(buf); 
                                break;

                                /* GPRS短信息*/
                        case PC_ARM_SEND_GPRS_MESSAGE_REQ:
                                send_gprs_message_req(buf);
                                break;
                
                                /* 发送ZIGBEE信息*/
                        case PC_ARM_SEND_ZIGBEE_MESSAGE_REQ:
                                send_zigbee_message_req(buf);
                                break;

                                /* 报警器控制*/
                        case PC_ARM_BEEP_CONTROL_REQ:
                                beep_control_req(buf);
                                break;

                                /* LED控制*/
                        case PC_ARM_LEDS_CONTROL_REQ:
                                led_control_req(buf);
                                break;

                                /* 硬件自检*/
                        case PC_ARM_HARDWARE_TESTSELF_REQ:
                                hardware_selftest_req(buf);
                                break;
                
                                /* 时间校准*/
                        case PC_ARM_TIME_ADJUST_REQ:
                                time_adjust(buf);
                                break;
                }

                /* 反馈消息*/
                if(sendto(server_sockfd, buf, len, 0, 
                                        (struct sockaddr *)&client_addr, sin_size) < 0) {
                        ERROR("send packet error\n");
                        return -1;
                }
        }
}
