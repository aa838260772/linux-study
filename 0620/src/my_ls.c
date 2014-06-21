/*************************************************************************
	> File Name: my_ls.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 11时26分54秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
DIR *dir;
struct dirent * mydir;
if(argc==1)
 dir=opendir("./");
else
	dir=opendir(argv[1]);
if(!dir)
{
printf("open dir failed!\n");
exit(-1);
}
while((mydir=readdir(dir))!=NULL)
printf("%d  %d  %d  %c  %s\n",mydir->d_reclen,mydir->d_off
		,mydir->d_ino,mydir->d_type,mydir->d_name);

return 0;
}
