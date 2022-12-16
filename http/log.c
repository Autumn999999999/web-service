#include "http.h"

void log_request(struct Request *req) {
    char *msg = malloc(sizeof(char) * DEFAULT_BUFLEN);
    memset(msg, 0, sizeof(char) * DEFAULT_BUFLEN);
    sprintf(msg, "[Request]: %s %s", info_str(req->method), req->path);
    log_msg(msg);
}

void log_response(struct Response *resp) {
    char *msg = malloc(sizeof(char) * DEFAULT_BUFLEN);
    memset(msg, 0, sizeof(char) * DEFAULT_BUFLEN);

    char *status = transfer_int_to_str(resp->statusCode);

    if(resp->statusCode == StatusOK){
        sprintf(msg, "[Response]: %s | %s\n", info_str(status), resp->body);
    }else{
        sprintf(msg, "[Response]: %s | %s\n", error_str(status), resp->body);
    }

    log_msg(msg);
}