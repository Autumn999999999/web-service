#include "http/http.h"
#include "core/core.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")



int main(){


    // 开启一个HTTP服务
    int iResult = serveHTTP(NULL);
    if (iResult == ERR){
        return 1;
    }
    return 0;
}

