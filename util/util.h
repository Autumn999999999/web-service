#ifndef WEB_SERVER_UTIL_H
#define WEB_SERVER_UTIL_H

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "../log/log.h"

#define OK 0
#define ERR -1

char *transfer_int_to_str(int num);
int transfer_str_to_int(char *str);

void print_banner();

#endif //WEB_SERVER_UTIL_H
