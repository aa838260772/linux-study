/*************************************************************************
	> File Name: linklist.h
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 10时07分24秒
 ************************************************************************/
#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include<stdio.h>
#include<stdlib.h>
typedef struct lnode{
	int num;
    struct lnode *next;
}lnode,*linklist;
void show(linklist);
void  link_create(linklist *);
void  link_reverse(linklist *);
void  link_merge(linklist *,linklist*);
void  link_delsame(linklist *,linklist *);
void  link_split(linklist *,linklist *);
#endif
