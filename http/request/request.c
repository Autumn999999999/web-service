#include "request.h"

struct Request *new_request(struct String *requestStr, SOCKET clientSocket) {
    struct Request *req = malloc(sizeof(struct Request));
    req->method = new_string("");
    req->path = new_string("");
    req->version = new_string("");
    req->body = new_string("");
    req->headerFormCount = 0;
    req->headerForms = NULL;
    req->bodyFormCount = 0;
    req->bodyForms = NULL;
    req->clientSocket = clientSocket;

    // 解析请求行
    parse_request_line(req, requestStr);

    // 解析请求头
    parse_request_header(req, requestStr);

    // 获取请求体
    if(strcmp(req->method->value, "POST") == 0){
        req->body = get_request_body(requestStr);
    }

    return req;
}

void parse_request_line(struct Request *req, struct String *requestStr) {

    struct String *requestLine = get_request_line(requestStr);

    requestLine = split_string(requestLine,NULL, ' ');
    req->method = copy_string(requestLine);
    req->version = copy_string(requestLine + 2);
    if(strcmp(req->version->value, "HTTP/1.1") != 0) {
        log_error("不支持的HTTP版本");
        return;
    }

    struct String *requestPath = copy_string(&requestLine[1]);
    requestPath = split_string(requestPath, NULL, '?');
    req->path = copy_string(&requestPath[0]);
    if(requestPath[1].length > 0){
        req->headerForms = parse_form(requestPath[1].value, &req->headerFormCount);
    }

    free_string(requestPath);
    free_string(requestLine);
}

void parse_request_header(struct Request *req, struct String *requestStr) {
    // 定位到请求头的开始位置
    struct String *requestHeader = get_request_header(requestStr);
    // 解析请求头
    int count;
    requestHeader = split_string_with_offset(requestHeader,&count, '\r',1);
    req->headerCount = count;
    req->headers = malloc(sizeof(struct Header) * count);

    for(int i = 0; i < count; i++){
        struct String *header = copy_string(requestHeader + i);
        header = split_string(header, NULL, ':');
        req->headers[i] = *new_header(header[0].value, header[1].value);
        free_string(header);
    }
}

void parse_request_body(struct Request *req) {
    if(strcmp(req->method->value, "POST") == 0){
        req->bodyForms = parse_form(req->body->value, &req->bodyFormCount);
    }
}

struct String *get_request_line(struct String *requestStr) {
    int index = index_of_char(requestStr, '\r');
    return sub_string(requestStr, 0, index);
}

struct String *get_request_header(struct String *requestStr) {
    int start = index_of_char(requestStr, '\r') + 2;
    int end = last_index_of_string(requestStr, "\r\n\r\n");
    return sub_string(requestStr, start, end);
}

struct String *get_request_body(struct String *requestStr) {
    int start = last_index_of_string(requestStr, "\r\n\r\n") + 4;
    return sub_string(requestStr, start, requestStr->length);
}

void free_request(struct Request *req) {
    free_string(req->method);
    free_string(req->path);
    free_string(req->version);
    free_string(req->body);
    for(int i = 0; i < req->headerFormCount; i++){
        free_form(&req->headerForms[i]);
    }
    for(int i = 0; i < req->bodyFormCount; i++){
        free_form(&req->bodyForms[i]);
    }
    free(req);
}