#include "form.h"

struct Form *new_form(char *key, char *value) {
    struct Form *form = malloc(sizeof(struct Form));
    form->key = new_string(key);
    form->value = new_string(value);
    return form;
}

void free_form(struct Form *form) {
    free_string(form->key);
    free_string(form->value);
    free(form);
}

struct Form *parse_form(char *str, int *count){
    if (str == NULL) {
        return 0;
    }

    struct String *newStr = new_string(str);
    int cnt;

   newStr = split_string_with_offset(newStr, &cnt, '&', 0);

   if(count != NULL) {
       *count = cnt;
   }

    struct Form *forms = malloc(sizeof(struct Form) * cnt);

    for (int i = 0; i < cnt; i++) {
        struct String *formStr = copy_string(newStr + i);
        formStr = split_string(formStr,NULL, '=');
        forms[i] = *new_form(formStr[0].value, formStr[1].value);
        free_string(formStr);
    }

    return forms;
}

char *get_header(struct Request *req, char *key) {
    for (int i = 0; i < req->headerCount; i++) {
        struct Header *header = &req->headers[i];
        if (strcmp(header->key->value, key) == 0) {
            return header->value->value;
        }
    }
    return NULL;
}

char *get_path_value(struct Request *req, char *key) {
    for(int i = 0 ; i < req->headerFormCount; i++){
        if(strcmp(req->headerForms[i].key->value, key) == 0){
            return req->headerForms[i].value->value;
        }
    }
    return NULL;
}

char *get_body_value(struct Request *req, char *key) {
    for(int i = 0 ; i < req->bodyFormCount; i++){
        if(strcmp(req->bodyForms[i].key->value, key) == 0){
            return req->bodyForms[i].value->value;
        }
    }
    return NULL;
}

char *get_value(struct Request *req, char *key) {
    char *value = get_path_value(req, key);
    if(value == NULL){
        value = get_body_value(req, key);
    }
    return value;
}