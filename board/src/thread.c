#include "device.h"
#include "msg.h"
#include "log.h"
#include "common.h"

int create_thread(void)
{
        int ret;

        /*创建监控线程： 
         *1.监控红外
         *2.监控温度
         *3.与webserver通信
         * */
        ret = pthread_create(&thread_temperature, NULL, thread_monitor_temperature, NULL); 
        if (ret != 0) {
               ERROR("create pthread for monitoring temperature error\n");
               return ret;
        }

        ret = pthread_create(&thread_infrared, NULL, thread_monitor_infrared, NULL);
        if (ret != 0) {
                ERROR("create pthread for monitoring infrared error\n");
                return ret;
        }

        ret = pthread_create(&thread_boa, NULL, thread_talkto_boa, NULL); 
        if (ret != 0){
                ERROR("create pthread for talking with boa error\n");
                return ret;
        }
        
        return ret;
}

/* 监控温度*/
void *thread_monitor_temperature(void *pdata)
{
       float temp;

       INFO("Start %s.", __func__);
       for (;;) {
                temp = get_temperature();
                if (temp > TEMPERATURE_ALARM) {
                        /* 开启报警器*/
                        start_alarm();
                        /* 发送短信息*/
                        send_gprs_message("15xxxxxxxxx", "home is firing!");
                }
                /* 每隔 3秒 采集*/
                sleep(3);
       }
}

/* 监控按键*/
void *thread_monitor_infrared(void *pdata)
{
        bool thief;
        
        INFO("Start %s.", __func__);
        for(;;) {
                thief = get_button_key();
                if (thief == true) {
                        /* 开启报警器*/
                        start_alarm();
                        /* 发送短信息*/
                        send_gprs_message("1234545555", "a thief at home!");
                }
        }
}

#define M_FINISHED      'F'
/* 与BOA通信*/
void *thread_talkto_boa(void *pdata)
{
        struct msg_buf  msg_sbuf, msg_rbuf;
        long mtype;
        int ret;

        /* 获取唯一键值*/
        INFO("Create MSG for BOA.");
        
        msgkey  = ftok(MSG_PATH, MSG_PROJ_ID);
        if (msgkey == -1) {
                ERROR("get msg key error\n");
                return NULL;
        }

        msgflag = IPC_CREAT | IPC_EXCL;
        msgid   = msgget(msgkey, msgflag);
        if (msgid == -1) {
                ERROR("get msg id error\n");
                return NULL;
        }
       
        for (;;) {
                /* 接受消息*/
                ret = msgrcv(msgid, &msg_rbuf, sizeof(msg_rbuf.mtext), 0, 0);
                if (ret == -1) {
                        ERROR("receive msg error\n");
                        return NULL;
                }
                
                switch(msg_rbuf.mtype) {
                        case M_REBOOT:
                                system_reboot();
                                break;
                        case M_OPEN_LED:
                                flash_led();
                                break;
                        case M_CLOSE_LED:
                                stop_led();
                                break;
                        case M_OPEN_ALARM:
                                start_alarm();
                                break;
                        case M_CLOSE_ALARM:
                                stop_alarm();
                                break;
                }

                msg_sbuf.mtype  = M_FINISHED;
                ret = msgsnd(msgid, &msg_sbuf, sizeof(msg_sbuf.mtext), 0);
                if (ret == -1) {
                        ERROR("send message to boa error\n");
                        return NULL;
                }
        }
}
