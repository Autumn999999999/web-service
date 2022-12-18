#include "http.h"

int serveHTTP(char *port,int option) {

    // 调用初始化函数，返回一个server socket
    // 参数为端口号，默认为3000
    SOCKET listenSocket = init_winSock(port);

    if (listenSocket == ERR) {
        printf("server failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return ERR;
    }

    // 打印banner
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

        // 读取并解析请求
        struct String *requestStr = read_request(ClientSocket);
        log_msg(requestStr->value);
        // 从请求报文中解析请求到request结构体中
        struct Request *req = new_request(requestStr, ClientSocket);

        // 处理请求
        handle_request(req,option);

    } while (1);

    closesocket(listenSocket);
    WSACleanup();
    return OK;
}

void handle404(struct Request *req,struct Response *resp){
    response_string(resp,StatusNotFound,"Not Found");
}

void handle_request(struct Request *req,int option) {
    struct Router *router = find_router(req);

    log_request(req);

    if(router == NULL && option & AUTO_METHOD){
        if(strcmp(req->method->value,"GET") == 0) {
            free_string(req->method);
            req->method = new_string("POST");
            router = find_router(req);
        }else if(strcmp(req->method->value,"POST") == 0) {
            free_string(req->method);
            req->method = new_string("GET");
            router = find_router(req);
        }
    }

    if(router == NULL &&
    option & HANDLE_Trailing_Slash &&
    req->path->value[req->path->length - 1] == '/' &&
    req->path->length > 1
    ){
        req->path->value[req->path->length - 1] = '\0';
        req->path->length--;
        router = find_router(req);
    }

    if(router == NULL){
        struct Response *resp = new_response(req);
        handle404(req,resp);
        log_response(resp);
        free_response(resp);
        return;
    }

    struct Response *resp = new_response(req);
    if(option & CORS){
        cors(resp);
    }

    router->handler(req,resp);

    log_response(resp);

    free_response(resp);
}

struct String *read_request(SOCKET ClientSocket) {
    int iResult;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    struct String *requestStr = new_string("");

    // 读取请求的所有内容
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        // 读取异常，退出循环
        if(iResult <= 0){
            break;
        }
        if(iResult < recvbuflen){
            recvbuf[iResult] = '\0';
        }
        // 将读取的内容追加到requestStr中
        append_string(requestStr, recvbuf);
        // 若读取长度小于缓冲区长度，说明已经读取完毕
        if(iResult < recvbuflen){
            break;
        }
    } while (1);

    return requestStr;
}