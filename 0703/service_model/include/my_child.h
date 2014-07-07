/*************************************************************************
  > File Name: my_child.h
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月03日 星期四 19时28分04秒
 ************************************************************************/

#ifndef _MY_CHILD_H_
#define _MY_CHILD_H_
#include "msg.h"
#define S_BUSY 1
#define S_IDLE 0
typedef struct tag
{
	pid_t s_pid;
	int s_status;//状态
	int s_read;
	int s_write;
	int s_cnt;
}CHLD,*pCHLD;
void make_chld(pCHLD,int);
void child_main();
#endif
