#include "core.h"

struct Item *new_items() {
    struct Item *items = malloc(sizeof(struct Item) * DEFAULT_ITEM_LEN);
    memset(items, 0, sizeof(struct Item) * DEFAULT_ITEM_LEN);
    return items;
}

char *json_item(struct Item *items,int len) {
    char *json = malloc(DEFAULT_LEN);
    char *temp = malloc(DEFAULT_LEN);
    memset(json, 0, DEFAULT_LEN*sizeof(char));
    memset(temp, 0, DEFAULT_LEN*sizeof(char));

    int jsonLen = DEFAULT_LEN / 2;
    int jsonCap = DEFAULT_LEN;

    strcpy(json, "[");
    for (int i = 0; i < len; i++) {
        sprintf(temp, "{\"date\":\"%s\",\"content\":\"%s\",\"itemType\":%d,\"type\":%d,\"money\":%d}", items[i].date, items[i].content, items[i].itemType, items[i].type, items[i].money);
        if(jsonLen + strlen(temp) + 1 > jsonCap){
            jsonCap *= 2;
            json = realloc(json, jsonCap);
        }
        strcat(json, temp);
        if (i != len - 1) {
            strcat(json, ",");
        }
    }
    strcat(json, "]");
    return json;
}

void response_item_json(struct Response *resp,struct Item *items,int len) {
    char *json = json_item(items,len);
    add_header(resp, "Content-Type", "application/json");
    response_string(resp, StatusOK, json);
}