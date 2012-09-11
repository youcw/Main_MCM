#include <stdio.h>  
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
    struct msginfo regs = {1001, 1002, 1003};
    struct msginfo tmp;

    int client_sockfd;
    int len;
    int sin_size;
    char buf[BUF_SIZE];
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    client_addr.sin_family      = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("192.168.0.100");   //无限制
    client_addr.sin_port        = htons(8000);

    if ((client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0) {
        ERROR("socket error\n");
        return -1;
    }

    sin_size = sizeof(struct sockaddr_in);
    
    INFO("send packet .....");

    strcpy(buf, "hello,world");
    for(;;) {
        /* 接收消息*/
        if((len = sendto(client_sockfd, &regs, sizeof(regs), 0, 
                    (struct sockaddr*)&client_addr, sin_size)) < 0) {
                ERROR("send packet error\n");
                return -1;
        }

        /* 反馈消息*/
        if((len = recvfrom(client_sockfd, buf, 
                        BUF_SIZE, 0, NULL, NULL)) < 0) {
                    ERROR("send packet error\n");
                    return -1;
        }
        memcpy(&tmp, buf, sizeof(tmp));
        INFO("msgid = %d addr = %d data = %d\n", 
                        tmp.msgid, tmp.addr, tmp.data); 
        sleep(1);
    }
}
