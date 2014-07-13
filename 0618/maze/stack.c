/*************************************************************************
	> File Name: stack.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: Wed 18 Jun 2014 11:36:30 PM CST
 ************************************************************************/
#include"stack.h"
void stack_init(pNODE *pst)
{
*pst=NULL;
}

void stack_push(pNODE *pst,Pos ps)
{
pNODE pCur=(pNODE)calloc(1,sizeof(NODE));
pCur ->s_ps=ps;
pCur ->s_next=*pst;
*pst=pCur;
}

void stack_pop(pNODE *pst)
{
pNODE p;
if(*pst)
{
p=*pst;
*pst=(*pst)->s_next;
free(p);
}
}

pNODE stack_top(pNODE pst)
{
return pst;
}

int stack_empty(pNODE *pst)
{
return (*pst==NULL);
}

void stack_reverse(pNODE *pst)
{
pNODE pCur,pNext,pPre;
pPre=NULL;
pCur=*pst;
if(!*pst)
	return;
pNext=(*pst)->s_next;
if(!pNext)
	return;
while(!pNext)
{
 pCur->s_next=pPre;
 pPre=pCur;
 pCur=pNext;
 pNext=pNext->s_next;
}
pCur->s_next=pPre;
*pst=pCur;
}

void stack_show(pNODE pst)
{
int i=0;
printf("\n");
while(pst)
{
	i++;
printf("(%d.%d)",(pst->s_ps).s_x,(pst->s_ps).s_y);
pst=pst->s_next;
if(i%10==0)
	printf("\n");
}
}












