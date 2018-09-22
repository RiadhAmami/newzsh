CC=gcc
SRC = ./src/*.c
EXE= myshell
CFLAGS=  -L/usr/local/lib -I/usr/local/include -lreadline
build:
	$(CC) -g  -o  $(EXE) $(SRC) $(CFLAGS) 
clean:
	rm myshell
rebuild:
	clean build
