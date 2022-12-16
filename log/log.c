#include "log.h"

FILE **writers;
int writerCount = 0;


void log_msg(char *msg) {
    if (writerCount == 0) {
        printf("%s\n",msg);
    }
    for (int i = 0; i < writerCount; i++) {
        fprintf(writers[i], "%s\n", msg);
    }
}

// 打印绿色，用于提示信息
void log_info(char *msg) {
    if (writerCount == 0) {
        printf("\033[32m%s\033[0m", msg);
        return;
    }
    for (int i = 0; i < writerCount; ++i) {
        fprintf(writers[i], "\033[32m%s\033[0m", msg);
    }
}

// 打印黄色，警告
void log_warn(char *msg) {
    if (writerCount == 0) {
        printf("\033[33m%s\033[0m", msg);
        return;
    }
    for (int i = 0; i < writerCount; ++i) {
        fprintf(writers[i], "\033[33m%s\033[0m", msg);
    }
}

// 打印红色，错误
void log_error(char *msg) {
    if (writerCount == 0) {
        printf("\033[31m%s\033[0m", msg);
        return;
    }
    for (int i = 0; i < writerCount; ++i) {
        fprintf(writers[i], "\033[31m%s\033[0m", msg);
    }
}

// 生成提示信息
char *info_str(char *msg) {
    char *str = malloc(sizeof(char) * (strlen(msg) + 10));
    sprintf(str, "\033[32m%s\033[0m", msg);
    return str;
}

// 生成警告信息
char *warn_str(char *msg) {
    char *str = malloc(sizeof(char) * (strlen(msg) + 10));
    sprintf(str, "\033[33m%s\033[0m", msg);
    return str;
}

// 生成错误信息
char *error_str(char *msg) {
    char *str = malloc(sizeof(char) * (strlen(msg) + 10));
    sprintf(str, "\033[31m%s\033[0m", msg);
    return str;
}

// 添加日志输出位置，支持标准输出和文件输出
void add_writer(FILE *writer) {
    if (writers == NULL) {
        writers = malloc(sizeof(FILE *));
    } else {
        writers = realloc(writers, sizeof(FILE *) * (writerCount + 1));
    }
    writers[writerCount] = writer;
    writerCount++;
}