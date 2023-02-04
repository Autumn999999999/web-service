#include "core.h"
#define FILENAME "item.txt"

struct String *json_item(struct Item items[],int len){
    struct String *str = new_string("");
    append_string(str,"[");
    for(int i = 0 ; i < len ; i++){
        append_string(str,"{");
        append_string(str,"\"type\":");
        char *temp = transfer_int_to_str(items[i].type);
        append_string(str,temp);
        append_string(str,",");

        append_string(str,"\"consumptionType\":");
        temp = transfer_int_to_str(items[i].consumptionType);
        append_string(str,temp);
        append_string(str,",");

        append_string(str,"\"money\":");
        temp = transfer_int_to_str(items[i].money);
        append_string(str,temp);
        append_string(str,",");

        append_string(str,"\"balance\":");
        temp = transfer_int_to_str(items[i].balance);
        append_string(str,temp);

        append_string(str,"}");
        if(i != len - 1)append_string(str,",");
    }
    append_string(str,"]");
    return str;
}


int load_item(struct Item items[])
{
    int i=0;
    FILE* fp = fopen(FILENAME,"r");
    while (!feof(fp))
    {
        fscanf(fp , "%d %d %d %d",items[i].type,items[i].money,items[i].consumptionType,items[i].balance);
        i++;
    }   
    fclose(fp);
}

int save_item(struct Item item){
    FILE* fp = fopen(FILENAME,"a");
    fprintf(fp , "%d %d %d %d\n", item.type,item.money,item.consumptionType,item.balance );
    fclose(fp);

}

