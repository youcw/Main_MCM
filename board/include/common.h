#ifndef __COMMON_H
#define __COMMON_H

#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

pthread_t       thread_temperature;
pthread_t       thread_infrared;
pthread_t       thread_boa;

extern int create_socket(void);
extern void *thread_talkto_boa(void *pdata);
extern void *thread_monitor_temperature(void *pdata);
extern void *thread_monitor_infrared(void *pdata);

#define MSG_PATH        "/var"
#define MSG_PROJ_ID     'b'

#define M_REBOOT        (1000) 
#define M_OPEN_LED      (1001)
#define M_CLOSE_LED     (1002)
#define M_OPEN_ALARM    (1003)
#define M_CLOSE_ALARM   (1004)

key_t   msgkey;
int     msgid;
int     msgflag;

struct msg_buf {
        long mtype;
        char mtext[1];
};

typedef enum __bool {false=0, true=1}bool;

#endif
