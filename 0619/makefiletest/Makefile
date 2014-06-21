./bin/main:./temp/linklist.o ./temp/link_reverse.o
	gcc -o ./bin/main ./temp/*.o
./temp/linklist.o:./src/linklist.c
	gcc -o ./temp/linklist.o -c ./src/linklist.c -I./include
./temp/link_reverse.o:./src/link_reverse.c
	gcc -o ./temp/link_reverse.o -c ./src/link_reverse.c -I./include
