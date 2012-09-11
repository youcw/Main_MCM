#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>

#define BUF_SIZE    1024
#define ERROR       printf
#define INFO        printf

struct msginfo {
    unsigned long msgid;
    unsigned long addr;
    unsigned long data
};

int main(void)
{
    struct msginfo *regs;

    int server_sockfd;
    int len;
    int sin_size;
    char buf[BUF_SIZE];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

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
    
    INFO("waiting for packet......");

    for(;;) {
        /* 接收消息*/
        if((len = recvfrom(server_sockfd, buf, BUF_SIZE, 0, 
                    (struct sockaddr*)&client_addr, &sin_size)) < 0) {
                ERROR("receive packet error\n");
                return -1;
        }
        /* 消息处理*/
        //memcpy(&regs, buf, sizeof(regs));
        regs = (struct msginfo *)buf;
        INFO("msgid = %d addr = %d data = %d\n", 
                        regs->msgid, regs->addr, regs->data);
        
        regs->addr = 2002;
        /* 反馈消息*/
        if(sendto(server_sockfd, buf, len, 0, 
                (struct sockaddr *)&client_addr, sin_size) < 0) {
                    ERROR("send packet error\n");
                    return -1;
        }
    }

    close(server_sockfd);
}
