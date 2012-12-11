#include "device.h"
#include "common.h"
#include "msg.h"
#include "log.h"
#include "socket.h"

/* 功能：建立socket，与PC进行通信，处理消息
 * 返回值：-1：失败；0：成功
 * 参数：无
 * */


int create_socket(void)
{
        fd_set  readfd; //读文件描述符集合
        int ret;
        STRU_MSG_HEAD msg_head;
        int len;
        char buf[SIZE]; //接收网络数据缓冲区6K

        memset(&server_addr, 0, sizeof(server_addr));

        /* 初始化网络信息*/
        server_addr.sin_family      = AF_INET;          //设置为IP通信
        server_addr.sin_addr.s_addr = INADDR_ANY;       //无限制
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
       
        for(;;) {
                /* 接收消息*/
                bzero(buf, SIZE);
                FD_ZERO(&readfd);
                FD_SET(zigbeefd, &readfd);
                FD_SET(server_sockfd, &readfd);
                
                ret = select(server_sockfd + 1, &readfd, NULL, NULL, NULL); 
                if (ret == -1) 
                        perror("select:");
                else if (ret == 0) 
                        printf("timeout.\n");
                else if (FD_ISSET(zigbeefd, &readfd)) {
                        printf("have a uart data...........\n");
                        if (read(zigbeefd, buf, SIZE) < 0) {
                                ERROR("read zigbee error\n");
                                continue;
                        }
                } else if (FD_ISSET(server_sockfd, &readfd)) {
                        printf("have a net data...........\n");
                        if((len = recvfrom(server_sockfd, buf, SIZE, 0, 
                                                        (struct sockaddr*)&client_addr, &sin_size)) < 0) {
                                ERROR("receive packet error\n");
                                continue;
                        }
                }
                /* 消息处理
                 * 解析消息头
                 * 分发消息
                 * */
                memcpy(&msg_head, buf, sizeof(msg_head));
                switch(msg_head.u16MsgType) {
                        /* 查看系统信息请求*/
                        case O_MCMMAIN_MACHINE_INFO_QUERY_REQ:
                                get_machine_info_req(buf);
                                break;

                        /* 设置寄存器请求*/
                        case O_MCMMAIN_SET_REGISTER_DATA_REQ:
                                set_register_data_req(buf);
                                break;
                        
                        /* 查询寄存器请求*/
                        case O_MCMMAIN_GET_REGISTER_DATA_REQ:
                                get_register_data_req(buf);
                                break;

                        /* 设置EEPROM请求*/
                        case O_MCMMAIN_SET_EEPROM_DATA_REQ:
                                set_eeprom_data_req(buf);
                                break;

                        /* 查询EEPROM请求*/
                        case O_MCMMAIN_GET_EEPROM_DATA_REQ:
                                get_eeprom_data_req(buf);
                                break;

                        /* 软件更新请求 */
                        case O_MCMMAIN_SOFTWARE_UPDATE_REQ:
                                software_update_req(buf);
                                break;

                        /* 发送短信息请求*/
                        case O_MCMMAIN_MODEM_REQ:
                                send_gprs_message_req(buf);
                                break;
                
                        /* 发送ZIGBEE信息请求*/
                        case O_MCMMAIN_ZIGBEE_REQ:
                                send_zigbee_message_req(buf);
                                break;

                        /* 报警器控制*/
                        case O_MCMMAIN_BEEP_REQ:
                                beep_control_req(buf);
                                break;

                        /* LED控制*/
                        case O_MCMMAIN_LED_REQ:
                                led_control_req(buf);
                                break;

                        /* 硬件自检*/
                        case O_MCMMAIN_HARDWARE_SELFTEST_REQ:
                                hardware_selftest_req(buf);
                                break;
                
                        /* 时间校准*/
                        case O_MCMMAIN_TOD_ADJUST_REQ:
                                time_adjust_req(buf);
                                break;

                        /* TODO: 查询软件版本*/
                        case O_MCMMAIN_VERSION_QUERY_REQ:
                                /* TODO:*/
                                break;
                } //end switch

        }//end for(;;)
} //end
