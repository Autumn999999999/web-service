#include "http.h"

void send_response(SOCKET clientSocket, struct Response *response) {

    int bodySize = (int)strlen(response->body);

    char *responseStr = malloc((DEFAULT_BUFLEN + bodySize) * sizeof(char) * 2);

    sprintf(responseStr, "%s %d %s\n", response->version, response->statusCode, response->status);
    for(int i = 0; i < response->headerCount; i++) {
        struct ContentType header = response->headers[i];
        sprintf(responseStr, "%s%s: %s\n", responseStr, header.type, header.value);
    }

    sprintf(responseStr, "%s\n%s", responseStr, response->body);

    send(clientSocket, responseStr, (int)strlen(responseStr), 0);
    log_response(response);
    closesocket(clientSocket);
}

// 配置CORS相关字段
void cors(struct Response *resp) {
    resp->headerCount = 5;
    resp->headers = malloc(sizeof(struct ContentType) * resp->headerCount);
    resp->headers[0].type = "Access-Control-Allow-Origin";
    resp->headers[0].value = "*";
    resp->headers[1].type = "Access-Control-Allow-Headers";
    resp->headers[1].value = "Content-Type";
    resp->headers[2].type = "Access-Control-Allow-Methods";
    resp->headers[2].value = "GET,POST,PUT,DELETE,OPTIONS";
    resp->headers[3].type = "Access-Control-Allow-Credentials";
    resp->headers[3].value = "true";
    resp->headers[4].type = "Access-Control-Max-Age";
    resp->headers[4].value = "3600";
}

struct Response *create_response() {
    struct Response *response = malloc(sizeof(struct Response));
    memset(response, 0, sizeof(struct Response));
    response->version = "HTTP/1.1";
    response->body = "";
    response->headerCount = 0;
    cors(response);
    return response;
}

void add_header(struct Response *response, char *type, char *value) {
    response->headerCount++;
    response->headers = realloc(response->headers, response->headerCount * sizeof(struct ContentType));
    response->headers[response->headerCount - 1].type = type;
    response->headers[response->headerCount - 1].value = value;
}

void response_string(struct Response *resp,int statusCode, char *body) {
    write_code(resp, statusCode);
    if(body != NULL) {
        resp->body = body;
    }
}