#include "net.h"
#include "../util/util.h"


// 初始化Winsock
// 返回值：成功返回监听套接字，失败返回SOCKET_INIT_ERROR
SOCKET init_winSock(char *port) {

    if (port == NULL) {
        port = DEFAULT_PORT;
    }

    // 定义并初始化变量
    WSADATA wsaData;

    SOCKET listenSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iResult;

    // Initialize Winsock, MAKEWORD(2,2)调用2.2版
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return ERR;
    }

    ZeroMemory(&hints, sizeof(hints));
    // AF_INET指定IPv4地址
    hints.ai_family = AF_INET;
    // SOCK_STREAM和IPPROTO_TCP指定TCP连接
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // 解析服务器地址和端口到result中
    iResult = getaddrinfo(NULL, port, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return ERR;
    }

    // 创建一个socket
    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return ERR;
    }

    // 绑定socket到服务器地址
    iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    // 释放result，不再需要
    freeaddrinfo(result);

    // 开始监听socket
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    return listenSocket;
}

