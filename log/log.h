#ifndef WEB_SERVER_LOG_H
#define WEB_SERVER_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_msg(char *msg);
void log_info(char *msg);
void log_warn(char *msg);
void log_error(char *msg);
char *info_str(char *msg);
char *warn_str(char *msg);
char *error_str(char *msg);
void add_writer(FILE *writer);

#endif //WEB_SERVER_LOG_H
