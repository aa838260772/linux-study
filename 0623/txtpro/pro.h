/************************************************************************
	> File Name: pro.h
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 18时42分06秒
 ************************************************************************/

#ifndef _PRO_H_
#define _PRO_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define MAX_LINE_LEN  (1<<15)
#define MAX_LEN (1<<10)//每行最大长度
typedef struct word{
char name[20];
int count;
}word;
void text_process(int,int,int*,int *);
void rd_in(word **,FILE *,int *,int *);
void quick_sort(word *[],int);
void line_pro(char **,FILE *);
int index_kmp(char *,char *);
void search_sub(char **,char *,int);
void pro_space(char *);
#endif
