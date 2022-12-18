#ifndef WEB_SERVER_REQUEST_H
#define WEB_SERVER_REQUEST_H

#include "../type/type.h"

// 一个请求报文的格式如下：
//GET /hello.txt HTTP/1.1
//User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3
//Host: www.example.com
//Accept-Language: en, mi
//
// body
//
// 请求结构体
struct Request {
    // 请求方法
    struct String *method;
    // 请求路径，不包括参数
    struct String *path;
    // 请求的版本
    struct String *version;

    // 请求体
    struct String *body;

    // 请求路径中的参数数量
    int headerFormCount;
    // 请求路径中的参数
    struct Form *headerForms;

    // 请求体中的参数数量
    int bodyFormCount;
    // 请求体中的参数
    struct Form *bodyForms;

    // 请求头中的Content-Type
    int headerCount;
    struct Header *headers;

    // 该请求客户端的socket
    SOCKET clientSocket;
};

struct Request *new_request(struct String *requestStr, SOCKET clientSocket);
void free_request(struct Request *req);

struct String *get_request_line(struct String *requestStr);
struct String *get_request_header(struct String *requestStr);
struct String *get_request_body(struct String *requestStr);

// 解析参数
void parse_request_line(struct Request *req, struct String *requestStr);
void parse_request_header(struct Request *req, struct String *requestStr);
void parse_request_body(struct Request *req);

// 用于获取请求中的参数，包括路径中的参数和请求体中的参数
char *get_value(struct Request *req, char *key);
// 用于获取请求路径中的参数
char *get_path_value(struct Request *req, char *key);
// 用于获取请求体中的参数
char *get_body_value(struct Request *req, char *key);




#endif //WEB_SERVER_REQUEST_H
