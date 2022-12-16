#ifndef WEB_SERVER_NET_H
#define WEB_SERVER_NET_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// 默认接收的请求大小
#define DEFAULT_BUFLEN 512
// 指定监听端口
#define DEFAULT_PORT "3000"


SOCKET init_winSock(char *port);

#endif //WEB_SERVER_NET_H
