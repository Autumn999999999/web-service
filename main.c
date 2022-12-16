#include "http/http.h"
#include "core/core.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void hello(struct Request *req, struct Response *resp) {
    parse_body(req);
    char *test = get_value(req, "test");
    response_string(resp,StatusOK, test);
}

void get_all_item(struct Request *req,struct Response *resp){

    struct Item *items = malloc(sizeof(struct Item) * 10);
    items[0].date = "2020-01-01";
    items[0].content = "test";
    items[0].itemType = 1;
    items[0].type = 1;
    items[0].money = 100;
    items[1].date = "2020-01-01";
    items[1].content = "test";
    items[1].itemType = 1;
    items[1].type = 1;
    items[1].money = 100;

    response_item_json(resp,items,2);
}

void get_item(struct Request *req,struct Response *resp){
    char *order = get_value(req,"order");
    int orderNum = transfer_str_to_int(order);
}

void add_item(struct Request *req,struct Response *resp){
    parse_body(req);
    char *content = get_body_value(req,"content");
    char *money = get_body_value(req,"money");
    char *str = malloc(1024);
    sprintf(str,"content: %s,money: %s",content,money);
    response_string(resp,StatusOK,str);
}

int main(){

    register_get("/", hello);
    register_post("/", hello);
    register_get("/items",get_all_item);
    register_post("/item",add_item);
    register_get("/item",get_item);

    // 开启一个HTTP服务
    int iResult = serveHTTP(NULL);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}

