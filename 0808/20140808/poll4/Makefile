.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=libecho.a
OBJS=Socket.o Rio.o TcpConnection.o PollPoller.o InetAddress.o TcpServer.o Thread.o Condition.o ThreadPool.o Exception.o Timer.o TimerThread.o
STARD=-std=c++0x -rdynamic
LINKS=-lpthread
$(BIN):$(OBJS)
	ar -crv $@   $^ 
	chmod +x $@
	rm -f *.o
	mkdir echo
	cp *.h echo/
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)
clean:
	rm -rf *.o $(BIN) echo
