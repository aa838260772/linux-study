/*************************************************************************
  > File Name: hton.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年07月02日 星期三 09时42分07秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define my_hton(ip) ((ip&0xff)<<24|(ip&(0xff<<8))<<8|(ip&(0xff<<16))>>8|(ip&(0xff<<24))>>24)
union ip_i{
	int num;
	unsigned  char ip[4];
};
int main()
{
	char ip[64];
	int i=0,j=0,s=0;
	printf("ip:");
	memset(ip,0,64);
	fgets(ip,64,stdin);
	//puts(ip);
	union ip_i a;
	while(ip[i]!='\n')
	{
		if(ip[i]!='.')
			s=10*s+ip[i]-'0';
		else
	  {
			a.ip[j++]=s;
			s=0;
			printf("%d\n",a.ip[j-1]);
		}
		i++;
	}
	a.ip[j]=s;
//	for(i=0;i<4;++i)
//		printf("%u ",a.ip[i]);
//	printf("\n");
	printf("%d   %x   %x\n",a.num,a.num,my_hton(a.num));
  memset(ip,0,64)  ;
  sprintf(ip,"%d.%d.%d.%d",a.ip[0],a.ip[1],a.ip[2],a.ip[3]);
  puts(ip);
	return 0;
}
