#ifndef WEB_SERVER_STRINGS_H
#define WEB_SERVER_STRINGS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_SIZE 1024

struct String {
    char *value;
    int length;
    int cap;
};


struct String *new_string(char *value);
struct String *copy_string(struct String *string);
void free_string(struct String *string);
void append_string(struct String *string, char *value);

int count_char(struct String *string, char c);
struct String *split_string(struct String *string, int *count,char c);
struct String *split_string_with_offset(struct String *string,int *count, char c, int offset);
struct String *sub_string(struct String *string, int start, int end);
int index_of_char(struct String *string, char c);
int index_of_string(struct String *string, char *value);
int last_index_of_char(struct String *string, char c);
int last_index_of_string(struct String *string, char *value);

#endif //WEB_SERVER_STRINGS_H
