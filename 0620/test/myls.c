/*************************************************************************
	> File Name: myls.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年06月20日 星期五 22时55分59秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
static void mode_to_str(mode_t,char*);
static void time_pro(char *);
int main(int argc,char **argv)
{
DIR * dir;
struct dirent *mydir;
struct stat mystat;
char str[256];
char str_mode[11];
char *p_time;
if(argc==1)
  {
  dir=opendir("./");
  }
else
	dir=opendir(argv[1]);
while((mydir=readdir(dir))!=NULL)
{
	memset(&mystat,0,sizeof(mystat));
	memset(str,0,256);
	memset(str_mode,0,11);
	if(argv[1])
		sprintf(str,"%s%s",argv[1],mydir->d_name);
	else
		sprintf(str,"%s%s","./",mydir->d_name);
    stat(str,&mystat);
	mode_to_str(mystat.st_mode,str_mode);
   p_time=ctime(&mystat.st_atime);
   time_pro(p_time);


printf("%s %d %s %s  %d %d %s %s\n ",str_mode,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name,getgrgid(mystat.st_gid)->gr_name,mystat.st_size,mystat.st_blocks,p_time+4,mydir->d_name );

}
return 0;
}

void mode_to_str(mode_t mod,char *str)
{
strncpy(str,"----------",10);
if(S_ISDIR(mod))
   str[0]='d';
if(mod&S_IRUSR)
    str[1]='r';
if(mod&S_IWUSR)
   str[2]='w';
if(mod&S_IXUSR)
   str[3]='x';

if(mod&S_IRGRP)
    str[4]='r';
if(mod&S_IWGRP)
   str[5]='w';
if(mod&S_IXGRP)
   str[6]='x';

if(mod&S_IROTH)
    str[7]='r';
if(mod&S_IWOTH)
   str[8]='w';
if(mod&S_IXOTH)
   str[9]='x';
}

void time_pro(char *str)
{
char *p=str;
while(*p)
	p++;
while(*p!=':')
   p--;
*p='\0';
}

