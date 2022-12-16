TARGET = web-server.exe
OBJ = http/*.c log/*.c net/*.c util/*.c core/*.c *.c


.PHONY: start
start: build
	./$(TARGET)

.PHONY: build
build:
	gcc $(OBJ) -lws2_32 -o $(TARGET)

.PHONY: clean
clean:
	rm *.exe



