#ifndef WEB_SERVER_ROUTE_H
#define WEB_SERVER_ROUTE_H

#include "../type/type.h"

#define DEFAULT_ROUTE_SIZE 64

// 路由结构体
// 存在了请求路径和请求方法对应的处理函数
struct Router{
    struct String *path;
    struct String *method;
    void (*handler)(struct Request *req, struct Response *resp);
};

void register_router(char *path, char *method, void (*handler)(struct Request *req, struct Response *resp));
void register_get(char *path, void (*handler)(struct Request *req, struct Response *resp));
void register_post(char *path, void (*handler)(struct Request *req, struct Response *resp));
struct Router *find_router(struct Request *req);
void free_router();


#endif //WEB_SERVER_ROUTE_H
