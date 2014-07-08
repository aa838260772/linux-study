/*************************************************************************
	> File Name: process.h
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月06日 星期日 16时41分38秒
 ************************************************************************/

#ifndef _PROCESS_H_
#define _PROCESS_H_
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <strings.h>
#define MSG_LEN (8192-4)
#define S_BUSY 1
#define S_IDLE 0
typedef struct tag
{
int s_len;
char s_msg[MSG_LEN];
}MSG;
typedef struct sockaddr_in SA;
typedef struct tag1
{
pid_t s_pid;
int s_status;
int s_fd_wr;
}CHLD,*PCHLD;

int  listen_socket(char*,char*);
int  make_child(PCHLD ,int );//此处的int是创建的最大子进程数
void handle_request(int);
void send_fd(int ,int);
void recv_fd(int ,int*);

#endif
