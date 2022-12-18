#ifndef WEB_SERVER_FORM_H
#define WEB_SERVER_FORM_H

#include "../type/type.h"

struct Form *new_form(char *key, char *value);
void free_form(struct Form *form);

struct Form *parse_form(char *str, int *count);

char *get_header(struct Request *req, char *key);
char *get_path_value(struct Request *req, char *key);
char *get_body_value(struct Request *req, char *key);
char *get_value(struct Request *req, char *key);

#endif //WEB_SERVER_FORM_H
