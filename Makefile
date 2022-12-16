TARGET = web-server.exe
OBJ = */*.c *.c

.PHONY: build
build:
	gcc $(OBJ) -lws2_32 -o $(TARGET)

start: build
	./$(TARGET)

.PHONY: clean
clean:
	rm *.exe




