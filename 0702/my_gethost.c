/*************************************************************************
  > File Name: my_gethost.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月02日 星期三 14时54分54秒
 ************************************************************************/

#include<stdio.h>
#include<netdb.h>
#include<string.h>
int main(int argc,char *argv[])
{
	struct hostent* my_ent;
	if(argc==1)
	{
//		char str[64];
//		memset(str,0,64);
//		gethostname(str,64);
  //      puts(str);
		my_ent=gethostbyname("localhost");
	}else
	{
		my_ent=gethostbyname(argv[1]);
	}
	char ** p=my_ent->h_addr_list;
	printf("hostname:%s\n",my_ent->h_name);
	printf("add_type:%d\n",my_ent->h_addrtype);
	printf("add_len:%d\n",my_ent->h_length);
	printf("add list:\n");
	for(;*p!=NULL;p++)
	{
		printf("%x\n",*(int *)*p);
	}
	return 0;
}
