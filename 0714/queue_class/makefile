.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=queue
OBJS=queue.o test.o
$(BIN):$(OBJS)
		$(CC) $(CFLAG) $^ -o $@
%.o:%.cpp
		$(CC) $(CLAGS) -c $< -o $@
clean:
		rm -f *.o $(BIN)
