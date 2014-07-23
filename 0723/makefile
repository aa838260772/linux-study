.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=open nonblock 
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAHS) -c $< -o $@
clear:
	rm -f *.o $(BIN)
