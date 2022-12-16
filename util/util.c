#include "util.h"

char *transfer_int_to_str(int num) {
    char *str = malloc(sizeof(char) * 10);
    memset(str, 0, sizeof(char) * 10);
    sprintf(str, "%d", num);
    return str;
}

int transfer_str_to_int(char *str) {
    int num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}

void print_banner() {
    FILE *fp = fopen("banner.txt", "r");
    char str[4096];
    while (fgets(str, 4096, fp) != NULL) {
        log_info(str);
    }
    fclose(fp);
}