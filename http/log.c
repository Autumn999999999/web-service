#include "http.h"

// 打印request日志
void log_request(struct Request *req) {
    char *msg = malloc(sizeof(char) * DEFAULT_BUFLEN);
    memset(msg, 0, sizeof(char) * DEFAULT_BUFLEN);
    sprintf(msg, "[Request]: %s %s", info_str(req->method->value), req->path->value);
    log_msg(msg);
}

// 打印response日志
void log_response(struct Response *resp) {
    char *msg = malloc(sizeof(char) * DEFAULT_BUFLEN);
    memset(msg, 0, sizeof(char) * DEFAULT_BUFLEN);
    sprintf(msg, "[Response]: %d %s\n%s", resp->statusCode, resp->status->value, resp->body->value);
    log_msg(msg);
}