#include "http.h"

int serveHTTP(char *port) {

    // 调用初始化函数，返回一个server socket
    // 参数为端口号，默认为3000
    SOCKET listenSocket = init_winSock(port);

    if (listenSocket == ERR) {
        printf("server failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    log_info("server started");
    print_banner();

    do{
        SOCKET ClientSocket = INVALID_SOCKET;

        // 接受客户端的连接
        ClientSocket = accept(listenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return ERR;
        }


        struct Request *req = parse_request(ClientSocket);
        req->clientSocket = ClientSocket;

        handle_request(req);

    } while (1);

    closesocket(listenSocket);
    WSACleanup();
    return OK;
}