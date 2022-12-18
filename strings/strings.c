#include "strings.h"

struct String *new_string(char *value) {
    if(value == NULL){
        value = "";
    }
    struct String *string = malloc(sizeof(struct String));
    int len = strlen(value);
    int cap = DEFAULT_SIZE;
    while (cap < len + 1) {
        cap *= 2;
    }
    string->value = malloc(cap);
    memset(string->value, 0, cap);

    strcpy(string->value, value);
    string->length = len;
    string->cap = cap;

    return string;
}

struct String *copy_string(struct String *string) {
    struct String *newString = malloc(sizeof(struct String));
    int len = string->length;
    int cap = string->cap;
    newString->value = malloc(cap);
    memset(newString->value, 0, cap);

    strcpy(newString->value, string->value);
    newString->length = len;
    newString->cap = cap;

    return newString;
}

void append_string(struct String *string, char *value) {
    int len = strlen(value);
    int newLen = string->length + len;
    if (newLen > string->cap) {
        int cap = string->cap;
        while (cap < newLen + 1) {
            cap *= 2;
        }
        string->value = realloc(string->value, cap);
        string->cap = cap;
    }
    strcpy(string->value + string->length, value);
    string->length = newLen;
}

struct String *sub_string(struct String *string, int start, int end) {
    if (start < 0 || end > string->length) {
        return NULL;
    }

    struct String *newString = malloc(sizeof(struct String));
    int len = end - start;
    int cap = DEFAULT_SIZE;
    while (cap < len + 1) {
        cap *= 2;
    }

    newString->value = malloc(cap);
    memset(newString->value, 0, cap);
    strncpy(newString->value, string->value + start, len);
    newString->length = len;
    newString->cap = cap;

    return newString;
}

int count_char(struct String *string, char c) {
    int count = 0;
    for (int i = 0; i < string->length; i++) {
        if (string->value[i] == c) {
            count++;
        }
    }
    return count;
}

// 按照指定字符分割字符串
struct String *split_string(struct String *string, int *count, char c) {
    return split_string_with_offset(string, count, c, 0);
}


// 按照指定字符分割字符串
// offset表示分割每一段字符串的起始位置偏移量
struct String *split_string_with_offset(struct String *string,int *count, char c, int offset) {
    int cnt = count_char(string, c) + 1;
    if(count != NULL){
        *count = cnt;
    }
    struct String *split = malloc(sizeof(struct String) * cnt);
    int start = 0;
    int num = 0;
    for (int i = 0; i < string->length; i++) {
        if (string->value[i] == c) {
            split[num++] = *sub_string(string, start, i);
            start = i + 1 + offset;
        }
    }
    split[cnt - 1] = *sub_string(string, start, string->length);
    free_string(string);
    return split;
}

int index_of_char(struct String *string, char c) {
    for (int i = 0; i < string->length; i++) {
        if (string->value[i] == c) {
            return i;
        }
    }
    return -1;
}

int index_of_string(struct String *string, char *value) {
    int len = strlen(value);
    for (int i = 0; i < string->length - len; i++) {
        if (strncmp(string->value + i, value, len) == 0) {
            return i;
        }
    }
    return -1;
}

int last_index_of_char(struct String *string, char c) {
    for (int i = string->length - 1; i >= 0; i--) {
        if (string->value[i] == c) {
            return i;
        }
    }
    return -1;
}

int last_index_of_string(struct String *string, char *value) {
    int len = strlen(value);
    for (int i = string->length - len; i >= 0; i--) {
        if (strncmp(string->value + i, value, len) == 0) {
            return i;
        }
    }
    return -1;
}

void free_string(struct String *string) {
    free(string->value);
    free(string);
}

