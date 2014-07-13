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
#include <sys/stat.h>
#include <fcntl.h>
#define MSG_LEN (8192-4)
typedef struct tag
{
int s_len;
char s_msg[MSG_LEN];
}MSG;
typedef struct sockaddr_in SA;
int  listen_socket(char*,char*);
void handle_request(int);
#endif
