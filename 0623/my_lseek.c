/*************************************************************************
	> File Name: my_lseek.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月23日 星期一 15时38分24秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
typedef struct stu{
int num;
char name[12];
}
int main(int argc,char **argv)
{
stu s[5]={{1,"l1"},{2,"l2"},{3,"l3"},{4,"l4"},{5,"l5"}};
int fd_rw,i; 
fd_rw=open(argv[1],O_RDWR|O_CREAT);
if(fd_rw==-1)
{
	printf("open fail!\n");
	exit(-1);
}
for(i=0;i<5;++i)
write(fd_rw,s[i],sizeof(stu));





return 0;
}
