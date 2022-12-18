#ifndef WEB_SERVER_HTTP_H
#define WEB_SERVER_HTTP_H

#include "request/request.h"
#include "response/response.h"
#include "route/route.h"
#include "form/form.h"
#include "type/type.h"

// 选项
#define CORS 1 << 0
#define HANDLE_Trailing_Slash 1 << 1
#define AUTO_METHOD 1 << 2

#define DEFAULT_OPTIONS CORS

struct String *read_request(SOCKET clientSocket);
// 处理请求
void handle_request(struct Request *req,int option);
// 打印请求日志
void log_request(struct Request *req);
// 打印响应日志
void log_response(struct Response *resp);
// 开启HTTP服务
int serveHTTP(char *port,int option);


#endif //WEB_SERVER_HTTP_H
