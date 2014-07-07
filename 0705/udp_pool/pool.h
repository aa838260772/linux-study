/*************************************************************************
	> File Name: pool.h
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月06日 星期日 10时02分44秒
 ************************************************************************/

#ifndef _POOL_H_
#define _POOL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/times.h>
#define MSG_LEN (8192-1024)
#define S_BUSY 1
#define S_IDLE 0
typedef struct sockaddr_in SA;
typedef struct tag{
pid_t s_pid;
int s_read;
int s_write;
int s_status;
int s_cnt;
}CHLD,*PCHLD;
int make_child(PCHLD,int);

#endif
