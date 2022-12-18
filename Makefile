# 目标exe
TARGET = web-server.exe

# 框架源文件
HTTP = http/*.c http/request/*.c http/route/*.c http/response/*.c http/form/*.c http/type/*.c \
log/*.c \
net/*.c \
util/*.c \
strings/*.c

# 核心功能实现源文件
CORE = src/core/*.c src/main.c $(HTTP)

# 案例源文件
EXAMPLE = example/*.c $(HTTP)


start: build
	./$(TARGET)

test:
	gcc $(EXAMPLE) -lws2_32 -o $(TARGET)
	./$(TARGET)

build:
	gcc $(CORE) -lws2_32 -o $(TARGET)

clean:
	rm *.exe



