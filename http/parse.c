#include "http.h"

// 获取请求的方法，路径，版本等
struct Request *parse(char *requestStr) {
    struct Request *req = malloc(sizeof(struct Request));
    memset(req, 0, sizeof(struct Request));

    // 解析请求体，这里获取body的方式是找到最后一个换行所在的位置，所以body中不能有换行，否则会出错
    char *body = strrchr(requestStr,'\n') + 1;

    // 解析请求头
    char *method = strtok(requestStr, " ");
    char *path = strtok(NULL, " ");
    char *version = strtok(NULL, "\r");

    if (strcmp(version, "HTTP/1.1") != 0){
        printf("version error");
        return NULL;
    }

    req->method = method;
    req->path = path;
    req->version = version;
    req->body = body;

    return req;
}

// 获取路径中的参数，并将path中的参数去掉
void parse_path(struct Request *req) {
    char *path = req->path;
    char *query = strchr(path, '?');

    if (query == NULL) {
        return;
    }

    *query = '\0';
    query = query + 1;

    req->headerForms = parse_form(query, &req->headerFormCount);
}

int parse_body(struct Request *req) {
    char *body = req->body;
    if (body == NULL || strlen(body) == 0) {
        return 0;
    }

    req->bodyForms = parse_form(body, &req->bodyFormCount);
}

struct Request *parse_request(SOCKET ClientSocket) {
    int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // 用于存储requestStr的长度最大容量
    int requestStrCap = DEFAULT_BUFLEN;
    // 当前requestStr的长度
    int requestStrLen = 0;

    char *requestStr = (char *) malloc(sizeof(char) * DEFAULT_BUFLEN);
    memset(requestStr, 0, sizeof(char) * DEFAULT_BUFLEN);

    // 读取请求的所有内容
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        // 读取异常，退出循环
        if(iResult <= 0){
            break;
        }
        if (iResult + requestStrLen < requestStrCap){
            strncat(requestStr, recvbuf, iResult);
        }else{
            // 扩容
            requestStrCap *= 2;
            requestStr = (char *) realloc(requestStr, sizeof(char) * requestStrCap);
            strncat(requestStr, recvbuf, iResult);
        }
        requestStrLen += iResult;
        // 若读取长度小于缓冲区长度，说明已经读取完毕
        if(iResult < recvbuflen){
            break;
        }
    } while (1);

    // 解析请求头
    struct Request *req = parse(requestStr);
    // 记录请求的信息
    log_request(req);

    // 解析请求路径
    parse_path(req);
    return req;
}



