#include "util.h"

char *transfer_int_to_str(int num) {
    char *str = malloc(sizeof(char) * 10);
    memset(str, 0, sizeof(char) * 10);
    sprintf(str, "%d", num);
    return str;
}