#include "../http/http.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void helloWorld(struct Request *req, struct Response *resp) {
    response_string(resp, StatusOK,"Hello World!");
}

void SayHello(struct Request *req, struct Response *resp) {
    parse_request_body(req);
    char *msg = get_value(req, "name");
    response_string(resp, StatusOK,msg);
}

int main(){

    register_get("/hello",helloWorld);
    register_post("/sayHello",SayHello);
    // 开启一个HTTP服务,参数为端口号
    int iResult = serveHTTP("3000",DEFAULT_OPTIONS);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}
