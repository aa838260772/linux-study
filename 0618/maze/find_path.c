/*************************************************************************
	> File Name: find_path.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: Wed 18 Jun 2014 11:53:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include"find_path.h"
static int find_next_dir(Pos pre,Pos cur);

int find_path(int maze[][COL+2],pNODE *pst)
{
pNODE pTop;
Pos offset[4]={{0,1},{1,0},{0,-1},{-1,0}};
int dir=0;
Pos pos_cur,pos_pre,pos_next,pos_des;
pos_cur.s_x=1;
pos_cur.s_y=1;

pos_des.s_x=ROW;
pos_des.s_y=COL;

while(pos_cur.s_x!=pos_des.s_x||pos_cur.s_y!=pos_des.s_y)
{
while(dir!=4)
{
pos_next.s_x=pos_cur.s_x+ offset[dir].s_x;
pos_next.s_y=pos_cur.s_y+ offset[dir].s_y;
if(maze[pos_next.s_x][pos_next.s_y]==0)
	break;
dir++;
}

if(dir==4)
{
 if(stack_empty(pst))
	    return 0;
 else
 {
  pTop=stack_top(*pst);
  pos_pre=pTop->s_ps;
  stack_pop(pst);
  dir=find_next_dir(pos_pre,pos_cur);
  pos_cur=pos_pre;
 }
}else
     {
     stack_push(pst,pos_cur);
     maze[pos_cur.s_x][pos_cur.s_y]=1;
     dir=0;
     }
 }

return 1;
}

int find_next_dir(Pos pre,Pos cur)
{
int x_delt,y_delt;
x_delt = cur.s_x - pre.s_x;
y_delt = cur.s_y - pre.s_y;
if(x_delt==0&&y_delt==1)
	return 1;
else if(x_delt==0&&y_delt==-1)
	return 3;
else if(x_delt==1&&y_delt==0)
	return 2;
else 
	return 4;
}
