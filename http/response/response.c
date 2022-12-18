#include "response.h"

void cors(struct Response *resp) {
    add_header(resp, "Access-Control-Allow-Origin", "*");
    add_header(resp, "Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    add_header(resp, "Access-Control-Allow-Headers", "Content-Type");
}

struct Response *new_response(struct Request *req) {
    struct Response *resp = malloc(sizeof(struct Response));
    resp->version = new_string("HTTP/1.1");
    resp->statusCode = StatusOK;
    resp->status = new_string("OK");
    resp->body = new_string("");
    resp->headerCount = 0;
    resp->headers = NULL;
    resp->req = req;
    return resp;
}


void free_response(struct Response *resp) {

    closesocket(resp->req->clientSocket);

    free_string(resp->body);
    free_string(resp->status);
    free_string(resp->version);
    for(int i = 0; i < resp->headerCount; i++) {
        free_string(resp->headers[i].key);
        free_string(resp->headers[i].value);
    }
    free(resp->headers);
    free_request(resp->req);
    free(resp);
}

void send_response(struct Response *resp) {
    struct String *responseStr = new_string("");

    char *msg = malloc(sizeof(char) * DEFAULT_BUFLEN);
    sprintf(msg, "%s %d %s\n", resp->version->value, resp->statusCode, resp->status->value);

    append_string(responseStr, msg);

    for(int i = 0; i < resp->headerCount; i++) {
        struct Header header = resp->headers[i];
        sprintf(msg, "%s: %s\n", header.key->value, header.value->value);
        append_string(responseStr, msg);
    }

    append_string(responseStr, "\n");
    append_string(responseStr, resp->body->value);

    send(resp->req->clientSocket, responseStr->value, responseStr->length, 0);

    free(msg);
    free_string(responseStr);
}

void response_string(struct Response *resp, int statusCode, char *body) {
    if(body == NULL) {
        body = "";
    }
    resp->statusCode = statusCode;
    write_code(resp, statusCode);
    append_string(resp->body, body);
    send_response(resp);
}

void write_code(struct Response *resp, int code) {
    resp->statusCode = code;
    free_string(resp->status);
    switch (code) {
        case StatusOK:
            resp->status = new_string("OK");
            break;
        case StatusBadRequest:
            resp->status = new_string("Bad Request");
            break;
        case StatusNotFound:
            resp->status = new_string("Not Found");
            break;
        case StatusInternalServerError:
            resp->status = new_string("Internal Server Error");
            break;
        default:
            resp->status = new_string("OK");
            break;
    }
}


void add_header(struct Response *resp, char *key, char *value) {
    if(resp->headerCount == 0) {
        resp->headers = malloc(sizeof(struct Header));
    } else {
        resp->headers = realloc(resp->headers, sizeof(struct Header) * (resp->headerCount + 1));
    }
    resp->headers[resp->headerCount] = *new_header(key, value);
    resp->headerCount++;
}
