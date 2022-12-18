#ifndef WEB_SERVER_RESPONSE_H
#define WEB_SERVER_RESPONSE_H

#include "../type/type.h"

// 响应报文格式示例：
//HTTP/1.1 200 OK
//Date: Mon, 27 Jul 2009 12:28:53 GMT
//Server: Apache
//Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
//ETag: "34aa387-d-1568eb00"
//Accept-Ranges: bytes
//Content-Length: 51
//Vary: Accept-Encoding
//Content-Type: text/plain
//
// body
//
// 响应结构体
struct Response {
    // 响应的版本
    struct String *version;
    // 响应的状态码
    int statusCode;
    // 响应的状态码对应的描述
    struct String *status;
    // 响应的内容
    struct String *body;

    // 响应头中的Content-Type
    int headerCount;
    struct Header *headers;

    struct Request *req;
};

struct Response *new_response(struct Request *req);
void free_response(struct Response *resp);
void add_header(struct Response *resp, char *key, char *value);
void write_code(struct Response *resp, int code);
void cors(struct Response *resp);
void response_string(struct Response *resp,int statusCode, char *body);

#endif //WEB_SERVER_RESPONSE_H
