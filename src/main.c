
#include "core/core.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

static int len=0;

static struct Item items[100];

void saveItem(struct Request *req, struct Response *resp ){
    parse_request_body(req);
    char *typeStr = get_value(req, "type");
    char *moneyStr = get_value(req, "money");
    char *consumptionTypeStr = get_value(req, "consumptionType");
    int type = transfer_str_to_int(typeStr);
    int money = transfer_str_to_int(moneyStr);
    int consumptionType = transfer_str_to_int(consumptionTypeStr);
    items[len].type = type;
    items[len].money = money;
    items[len].consumptionType = consumptionType;
    save_item(items[len]);
    len++;
    printf("len %d\n",len);
    response_string(resp, StatusOK,"ok");

}

void getItem(struct Request *req, struct Response *resp){
    struct String  *a = json_item(items,len);
    response_string(resp, StatusOK,a->value);

}

int main(){
    len = load_item(items);
    register_get("/getItem",getItem);
    register_post("/saveItem",saveItem);


    // 开启一个HTTP服务,参数为端口号
    int iResult = serveHTTP("3000",DEFAULT_OPTIONS);
    if (iResult == ERR){
        return 1;
    }



    return 0;
}

