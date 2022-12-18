#include "../http/http.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int main(){
    // 开启一个HTTP服务,参数为端口号
    int iResult = serveHTTP("3000",DEFAULT_OPTIONS);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}
