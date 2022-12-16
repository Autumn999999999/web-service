#include "http.h"

#define DEFAULT_MAX_ROUTE 100


struct Route *routes[DEFAULT_MAX_ROUTE];
int routeCount = 0;

void handle404(struct Request *req,struct Response *resp){
    response_string(resp,StatusNotFound,"404 Not Found");
}


void handle_request(struct Request *req) {

    int index = -1;

    for (int i = 0; i < routeCount; i++) {
        struct Route *route = routes[i];
        if (strcmp(route->path, req->path) == 0 && strcmp(route->method, req->method) == 0) {
            index = i;
            break;
        }
    }


    struct Response *resp = create_response();
    if(index == -1) {
        handle404(req, resp);
    } else {
        routes[index]->handler(req, resp);
    }

    send_response(req->clientSocket, resp);
    free(resp);
}

void register_route(char *path, char *method, void (*handler)(struct Request *req, struct Response *resp)) {

    if(routeCount >= DEFAULT_MAX_ROUTE){
        printf("Route count exceed");
        return;
    }

    struct Route *route = malloc(sizeof(struct Route));
    route->path = path;
    route->method = method;
    route->handler = handler;
    routes[routeCount++] = route;
}

void register_get(char *path, void (*handler)(struct Request *req, struct Response *resp)) {
    register_route(path, "GET", handler);
}

void register_post(char *path, void (*handler)(struct Request *req, struct Response *resp)) {
    register_route(path, "POST", handler);
}


