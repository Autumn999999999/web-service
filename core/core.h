#ifndef WEB_SERVER_CORE_H
#define WEB_SERVER_CORE_H

#include "../http/http.h"
#include <stdio.h>

#define DEFAULT_LEN 1024
#define DEFAULT_ITEM_LEN 10

struct Item{
    char *date;
    char *content;
    int itemType;
    int type; // 收支类型
    int money;
};

struct Item *new_items();

char *json_item(struct Item *items,int len);
void response_item_json(struct Response *resp,struct Item *items,int len);

void save_item(struct Item *items,int len);
int read_item(struct Item *items);

void register_routes();

#endif //WEB_SERVER_CORE_H
