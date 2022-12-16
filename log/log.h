#ifndef WEB_SERVER_LOG_H
#define WEB_SERVER_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 打印黑色信息
void log_msg(char *msg);
// 打印绿色信息
void log_info(char *msg);
// 打印黄色信息
void log_warn(char *msg);
// 打印红色信息
void log_error(char *msg);
char *info_str(char *msg);
char *warn_str(char *msg);
char *error_str(char *msg);
void add_writer(FILE *writer);

#endif //WEB_SERVER_LOG_H
