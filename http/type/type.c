#include "type.h"

struct Header *new_header(char *key, char *value) {
    struct Header *header = malloc(sizeof(struct Header));
    header->key = new_string(key);
    header->value = new_string(value);
    return header;
}