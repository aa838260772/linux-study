/*************************************************************************
  > File Name: test.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月06日 星期日 19时14分37秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc,char** argv)
{
	unsigned int t= inet_addr(argv[1]);
	unsigned int b;
	 int t1= inet_addr(argv[1]);
	 int b1;
	printf("%u  %x %d\n",t,t,t1);
	FILE *fp = fopen("a.txt","w");
	fprintf(fp,"%u %d",t,t1);
    fflush(fp);

	FILE *fp1=fopen("a.txt","r");
	fscanf(fp1,"%u %d",&b,&b1);
	printf("b:%u b1:%d\n",b,b1);
	fclose(fp);
	fclose(fp1);
	return 0;
}
