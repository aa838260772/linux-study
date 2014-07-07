#ifndef POOL_H
#define POOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MSG_LEN  (8192-16)
#define  S_IDLE  0
#define  S_BUSY  1
typedef struct sockaddr_in SA;
typedef struct tag
{
	pid_t s_pid;
	int s_read;
	int s_write;
	int s_cnt;
	int s_status;
}CHLD;
int make_main(CHLD * , int);
#endif
