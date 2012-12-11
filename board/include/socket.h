#ifndef __SOCKET_H
#define __SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define     SIZE    (1024 * 6)
int server_sockfd;
int sin_size;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;

#endif
