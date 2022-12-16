#include "http.h"

void write_code(struct Response *resp, int code){
    switch (code){
        case 200:
            resp->statusCode = 200;
            resp->status = "OK";
            break;
        case 404:
            resp->statusCode = 404;
            resp->status = "Not Found";
            break;
        case 500:
            resp->statusCode = 500;
            resp->status = "Internal Server Error";
            break;
        default:
            resp->statusCode = 200;
            resp->status = "OK";
            break;
    }
}