.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test_main
OBJS=buff.o con.o pro.o factory.o queue.o test_main.o
$(BIN):$(OBJS)
		$(CC) $(CFALGS) $^ -o $@ -lpthread
%.o:%.cpp
		$(CC) $(CFALGS) -c $< -o $@ -lpthread
clean:
		rm -f *.o
