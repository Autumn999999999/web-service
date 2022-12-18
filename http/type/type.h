#ifndef WEB_SERVER_TYPE_H
#define WEB_SERVER_TYPE_H

#include "../../net/net.h"
#include "../../util/util.h"
#include "../../log/log.h"
#include "../../strings/strings.h"
#include "../request/request.h"
#include "../response/response.h"
#include "../route/route.h"
#include "../form/form.h"

// 状态码
#define StatusOK 200
#define StatusBadRequest 400
#define StatusNotFound 404
#define StatusInternalServerError 500

// 存放key和value
// 存放请求路径和请求体中的参数
struct Form {
    struct String *key;
    struct String *value;
};

// 消息报头的结构体
struct Header {
    struct String *key;
    struct String *value;
};

struct Header *new_header(char *key, char *value);



#endif //WEB_SERVER_TYPE_H
