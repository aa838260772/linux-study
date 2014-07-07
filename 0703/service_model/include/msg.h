/*************************************************************************
	> File Name: msg.h
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月03日 星期四 09时58分12秒
 ************************************************************************/

#ifndef _MSG_H_
#define _MSG_H_
#define MSG_SIZE 8188
#define MSG_LEN (8192-MSG_SIZE)
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
typedef struct tag1
{
int s_len;
char s_buf[MSG_SIZE];
}MSG;
int listen_fd(char *,char *);
void handle_request(int);

#endif
