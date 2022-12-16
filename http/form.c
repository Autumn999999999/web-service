#include "http.h"

struct Form *parse_form(char *formStr, int *formCount) {
    if(formStr == NULL){
        return 0;
    }

    int len = strlen(formStr);
    char *str = malloc(len + 1);
    for(int i = 0; i < len; i++){
        str[i] = formStr[i];
    }
    str[len] = '\0';

    *formCount = 1;

    for(int i = 0; i < strlen(formStr); i++){
        if(formStr[i] == '&'){
            (*formCount)++;
        }
    }

    struct Form *forms = malloc(sizeof(struct Form) * *formCount);
    memset(forms, 0, sizeof(struct Form) * *formCount);

    for(int i = 0; i < *formCount; i++){
        char *key = strtok(str, "=");
        char *value = strtok(NULL, "&");
        str = value + strlen(value) + 1;
        forms[i].key = key;
        forms[i].value = value;
    }

    return forms;
}

char *get_header_value(struct Request *req, char *key){
    for(int i = 0; i < req->headerFormCount; i++){
        if(strcmp(req->headerForms[i].key, key) == 0){
            return req->headerForms[i].value;
        }
    }
    return NULL;
}

char *get_body_value(struct Request *req, char *key){
    for(int i = 0; i < req->bodyFormCount; i++){
        if(strcmp(req->bodyForms[i].key, key) == 0){
            return req->bodyForms[i].value;
        }
    }
    return NULL;
}

char *get_value(struct Request *req, char *key){
    char *value = get_header_value(req, key);
    if(value == NULL){
        value = get_body_value(req, key);
    }
    return value;
}