#include "route.h"

struct Router *routes[DEFAULT_ROUTE_SIZE];
int routeSize = 0;

struct Router *new_router(char *path, char *method, void (*handler)(struct Request *req, struct Response *resp)) {
    struct Router *router = malloc(sizeof(struct Router));
    router->path = new_string(path);
    router->method = new_string(method);
    router->handler = handler;
    return router;
}

void register_router(char *path, char *method, void (*handler)(struct Request *req, struct Response *resp)) {
    if(routeSize >= DEFAULT_ROUTE_SIZE){
        printf("路由数量已达上限");
        return;
    }
    struct Router *router = new_router(path, method, handler);
    routes[routeSize++] = router;
}

void register_get(char *path, void (*handler)(struct Request *req, struct Response *resp)) {
    register_router(path, "GET", handler);
}

void register_post(char *path, void (*handler)(struct Request *req, struct Response *resp)) {
    register_router(path, "POST", handler);
}

struct Router *find_router(struct Request *req) {
    for (int i = 0; i < routeSize; ++i) {
        struct Router *router = routes[i];
        if (strcmp(router->path->value, req->path->value) == 0 && strcmp(router->method->value, req->method->value) == 0) {
            return router;
        }
    }
    return NULL;
}


void free_router() {
    for(int i = 0; i < routeSize; i++){
        free_string(routes[i]->path);
        free_string(routes[i]->method);
        free(routes[i]);
    }
}