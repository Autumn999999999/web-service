#include "http/http.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void hello(struct Request *req, struct Response *resp) {
    parse_body(req);
    char *test = get_value(req, "tet");
    response_string(resp,StatusOK, test);
}

void test(struct Request *req, struct Response *resp) {
    FILE *fp = fopen("D:\\code\\Clion\\web-server\\index.html", "r");
    char *content = malloc(sizeof(char) * 4080);
    memset(content, 0, sizeof(char) * 4080);
    fread(content, sizeof(char), 4080, fp);

    add_header(resp, "Content-Type", "text/html");

    response_string(resp,StatusBadRequest, content);
}

int main()
{


    register_get("/", hello);
    register_post("/", hello);

    register_get("/test", test);

    // 开启一个HTTP服务
    int iResult = serveHTTP(NULL);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}

