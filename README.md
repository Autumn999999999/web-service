# WEB-SERVER使用指南

## 1. 背景
基于开发一个WEB项目的需求，需要使用C语言搭建一个WEB服务器，实现WEB服务器的基本功能。

## 2. 简介
web-server是一个基于C语言的WEB服务器，实现了WEB服务器的基本功能，包括：
- [X] 支持GET和POST方法
- [X] 封装HTTP请求和响应
- [X] 日志记录
- [X] 注册路由
- [ ] 支持静态资源请求

目录结构如下：
```
.
├── README.md // 项目说明
├── Makefile // 编译脚本
├── .gitignore // git忽略文件
├── http // http相关,包含http核心代码
├── log // 日志相关
├── net // socket相关
├── strings // 字符串封装
├── utils // 工具函数
├── example // 示例
├── src // 源代码文件夹
│   ├── main.c // 主函数
         ...
```

项目相关代码逻辑请在`src`文件夹下查看。
查看示例代码请在`example`文件夹下查看。

## 3. 快速开始

一个简单的GET请求示例：
```c
#include "../http/http.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void helloWorld(struct Request *req, struct Response *resp) {
    response_string(resp, StatusOK,"Hello World!");
}

int main(){
    register_get("/hello",helloWorld);
    // 开启一个HTTP服务,参数为端口号
    int iResult = serveHTTP("3000",DEFAULT_OPTIONS);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}
```

一个简单的POST请求示例：
```c
#include "../http/http.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void SayHello(struct Request *req, struct Response *resp) {
    parse_request_body(req);
    char *msg = get_value(req, "name");
    response_string(resp, StatusOK,msg);
}

int main(){
    register_post("/sayHello",SayHello);
    // 开启一个HTTP服务,参数为端口号
    int iResult = serveHTTP("3000",DEFAULT_OPTIONS);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}
```

## 4. 函数说明

### 4.1 HTTP相关函数
```c

```