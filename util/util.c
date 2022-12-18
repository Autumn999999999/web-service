#include "util.h"

// 把一个整数转换成字符串
char *transfer_int_to_str(int num) {
    char *str = malloc(sizeof(char) * 10);
    memset(str, 0, sizeof(char) * 10);
    sprintf(str, "%d", num);
    return str;
}

// 把一个字符串转换成整数
int transfer_str_to_int(char *str) {
    int num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}

// 打印banner
void print_banner() {
    FILE *fp = fopen("banner.txt", "r");
    char str[4096];
    while (fgets(str, 4096, fp) != NULL) {
        log_info(str);
    }
    fclose(fp);
}
