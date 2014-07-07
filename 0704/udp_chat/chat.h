#ifndef _CHAT_H_
#define _CHAT_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MSG_USR 1
#define MSG_GRP 2
#define MSG_ON 3
#define MSG_OFF 4
#define MSG_LEN (8192-8)
typedef struct sockaddr_in  SA;
typedef struct tag
{
int s_type;
int s_len;
SA s_addr;
char  s_msg[MSG_LEN];
}MSG;

typedef struct tag1
{
SA s_addr;
struct tag1 *s_next;
}Node,*pNode;
#endif
