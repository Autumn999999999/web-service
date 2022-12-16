#ifndef WEB_SERVER_HTTP_H
#define WEB_SERVER_HTTP_H

#include "../net/net.h"
#include "../util/util.h"
#include "../log/log.h"
#include "../core/core.h"


#define StatusOK 200
#define StatusBadRequest 400
#define StatusNotFound 404
#define StatusInternalServerError 500




struct ContentType {
    char *type;
    char *value;
};

struct Form {
    char *key;
    char *value;
};

struct Request {
    char *method;
    char *path;
    char *version;

    char *body;

    int headerFormCount;
    struct Form *headerForms;

    int bodyFormCount;
    struct Form *bodyForms;

    SOCKET clientSocket;
};

struct Response {
    char *version;
    int statusCode;
    char *status;
    char *body;

    int headerCount;
    struct ContentType *headers;
};


struct Route{
    char *path;
    char *method;
    void (*handler)(struct Request *req, struct Response *resp);
};

void register_route(char *path, char *method,void (*handler)(struct Request *req, struct Response *resp));
void register_get(char *path, void (*handler)(struct Request *req, struct Response *resp));
void register_post(char *path, void (*handler)(struct Request *req, struct Response *resp));

struct Form *parse_form(char *formStr, int *formCount);
struct Request *parse_request(SOCKET clientSocket);
int parse_body(struct Request *req);

void handle_request(struct Request *req);

char *get_value(struct Request *req, char *key);
char *get_header_value(struct Request *req, char *key);
char *get_body_value(struct Request *req, char *key);

void write_code(struct Response *resp, int code);

void log_request(struct Request *req);
void log_response(struct Response *resp);

void add_header(struct Response *resp, char *type, char *value);
struct Response *create_response();
void send_response(SOCKET clientSocket, struct Response *resp);
void response_string(struct Response *resp,int statusCode, char *body);

int serveHTTP(char *port);


#endif //WEB_SERVER_HTTP_H
