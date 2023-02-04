#ifndef WEB_SERVER_CORE_H
#define WEB_SERVER_CORE_H
#define meal 1
#define shop 2


#include "../../http/http.h"

struct Item
{ 
    int type;
    int consumptionType;
    int money;
    int balance;
};

struct String *json_item(struct Item items[],int len);
    
int load_item(struct Item items[]);

int save_item(struct Item item);



















#endif //WEB_SERVER_CORE_H

