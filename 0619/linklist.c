/*************************************************************************
	> File Name: linklist.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月19日 星期四 10时13分01秒
 ************************************************************************/

#include"linklist.h"
void link_create(linklist *h)
{
linklist p=*h,q;
*h=NULL;
q=*h;
int x;
printf("x:");
while(fflush(stdin),scanf("%d",&x),x!=9999)
{
p=(linklist)calloc(1,sizeof(lnode));
p->num=x;
p->next=NULL;
if(!*h)
{
p->next=*h;
*h=p;
q=p;
}
else
{
q->next=p;
q=p;
}
printf("x:");
}
}
void link_reverse(linklist *h)
{
linklist pre,cur,nex;
cur=*h,pre=NULL;
if(!*h)
	return;
nex=cur->next;
if(!nex)
	return;
while(nex)
{
cur->next=pre;
pre=cur;
cur=nex;
nex=nex->next;
}
cur->next=pre;
*h=cur;
}

void show(linklist h)
{
if(!h)
	return;
while(h)
{
printf("%3d ",h->num);
h=h->next;
}
 printf("\n");
}

void link_merge(linklist *h1,linklist *h2)
{
linklist p,q,h,r;
p=*h1;q=*h2;
if(!*h1)
	show(*h2);
else if(!*h2)
	show(*h1);
if((*h1)->num<(*h2)->num)
   {
   h=*h1;
   p=p->next;
   }
else
{
h=*h2;
q=q->next;
}
r=h;
while(p&&q)
{
if(p->num<q->num)
{
	r->next=p;
	r=p;
	p=p->next;
}
else
{
r->next=q;
r=q;
q=q->next;
}
}
if(p)
	r->next=p;
if(q)
	r->next=q;
show(h);
}

void link_delsame(linklist *h1,linklist *h2)
{
linklist p=*h1,q,pre=NULL;
while(p)
{
q=*h2;
while(q&&q->num!=p->num)
    q=q->next;
if(!q)
{
pre=p;
p=p->next;
}
else
{
if(p==*h1)
{
	(*h1)=(*h1)->next;
	p=(*h1);
}
else
    {
       pre->next=p->next;
	   p=p->next;
	}
}
}
}

void link_split(linklist *h1,linklist *h2)
{
int i=1;
linklist p=*h1,q=*h2,r=NULL;
*h2=NULL;
while(p)
{
if(i%2==0)
{
r->next=p->next;
if(!*h2)
{
*h2=p;
q=p;
}else
{ 
  q->next=p;
   q=p;
}
}
else
{
	r=p;
}
p=p->next;
i++;
}
q->next=NULL;

}










