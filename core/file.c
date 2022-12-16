#include "core.h"

// TODO: 用于处理文件，从文件中获取信息
struct Item *cache_items;
int cache_item_len = 0;
// 当前缓存是否可用，1表示可用
int cache_flag = 0;

void save_item(struct Item *items,int len){
    FILE *fp = fopen("item.txt","a");
    for(int i = 0 ; i < len ; i++){
        fprintf(fp,"%s %d\n",items[i].content,items[i].money);
    }
    fclose(fp);
    cache_flag = 0;
}

int read_item(struct Item *items){
    if(cache_flag){
        items = cache_items;
        return cache_item_len;
    }
    FILE *fp = fopen("item.txt","r");
    int count = 0;
    while(fscanf(fp, "%s %d", items[count].content, &items[count].money) != EOF){
        count++;
    }
    cache_items = items;
    cache_flag = 1;
    fclose(fp);
    return count;
}