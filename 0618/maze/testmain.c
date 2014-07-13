/*************************************************************************
	> File Name: testmain.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: Thu 19 Jun 2014 12:35:37 AM CST
 ************************************************************************/

#include<stdio.h>
#include "find_path.h"
int main()
{
pNODE MyStack;
int x,y;
int maze[ROW+2][COL+2]={
1,1,1,1,1,1,1,1,1,1,1,1,
1,0,1,1,1,1,1,1,1,1,1,1,
1,0,0,1,1,1,1,1,1,1,1,1,
1,0,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,1,1,1,1,1,1,1,1,
1,1,0,1,1,1,1,1,1,1,1,1,
1,1,0,0,1,1,1,1,1,1,1,1,
1,1,1,0,1,1,1,1,1,1,1,1,
1,1,1,0,0,0,0,1,1,1,1,1,
1,1,1,0,1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,0,1,
1,1,1,1,1,1,1,1,1,1,1,1
};
for(x=1;x<=ROW;++x)
{
for(y=1;y<=COL;++y)
printf("%d",maze[x][y]);
printf("\n");
}
stack_init(&MyStack);
if(find_path(maze,&MyStack))
{
stack_reverse(&MyStack);
stack_show(MyStack);
}else
{
printf("no path \n");
}
return 0;
}	
