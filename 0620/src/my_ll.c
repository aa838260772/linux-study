/*************************************************************************
	> File Name: my_ls.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 11时26分54秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
void str_time(char *);
void mode_to_str(mode_t,char *);

int main(int argc,char **argv)
{
DIR *dir;
struct dirent * mydir;
struct stat mystat;
char* pro_time;
char str[256];
char mode_str[11];
if(argc==1)
 dir=opendir("./");
else
{
	dir=opendir(argv[1]);
//	printf("%s\n",getcwd(NULL,0));
//  chdir(argv[1]);
}
if(!dir)
{
printf("open dir failed!\n");
exit(-1);
}
printf("mode      nlink uid   gid    size    a_tine    name\n");
while((mydir=readdir(dir))!=NULL)
{
memset(&mystat,0,sizeof(mystat));
memset(mode_str,0,11);
memset(str,0,256);
if(argv[1])
 sprintf(str,"%s%s",argv[1],mydir->d_name);
else
	sprintf(str,"%s%s","./",mydir->d_name);
//printf("%s\n",mydir->d_name);
stat(str,&mystat);
//stat(argv[1],&mystat);
pro_time=ctime(&mystat.st_ctime);
str_time(pro_time);
mode_to_str(mystat.st_mode,mode_str);

printf("%s  %d  %-5s  %5s %5d %-10s  %-10s\n",mode_str,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name,getgrgid(mystat.st_gid)->gr_name,mystat.st_size,pro_time+4,mydir->d_name);
}
return 0;
}

void str_time(char *str1)
{
char *str=str1;
while(*str)
  str++;
while(*str!=':')
	str--;
*str='\0';
}

void mode_to_str(mode_t x,char *str)
{
strncpy(str,"----------",10);
if(S_ISDIR(x))
         str[0]='d';
if(x&S_IRUSR)
   str[1]='r';
if(x&S_IWUSR)
	str[2]='w';
if(x&S_IXUSR)
str[3]='x';
if(x&S_IRGRP)
   str[4]='r';
if(x&S_IWGRP)
	str[5]='w';
if(x&S_IXGRP)
	str[6]='x';
if(x&S_IROTH)
   str[7]='r';
if(x&S_IWOTH)
str[8]='w';
if(x&S_IXOTH)
	str[9]='x';
}
