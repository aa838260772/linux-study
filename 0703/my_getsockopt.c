/*************************************************************************
	> File Name: my_getsockopt.c
	> Author: One
	> Mail:838260772@qq.com 
	> Created Time: 2014年07月03日 星期四 09时28分38秒
 ************************************************************************/

#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
int sock_fd;
int recv_size=0,snd_size=0;
int reuse = -1;
int len_recv=sizeof(int);
int len_snd=sizeof(int);
int len_reuse=sizeof(int);
sock_fd=socket(AF_INET,SOCK_STREAM,0);
getsockopt(sock_fd,SOL_SOCKET,SO_RCVBUF,&recv_size,&len_recv);
getsockopt(sock_fd,SOL_SOCKET,SO_SNDBUF,&snd_size,&len_snd);
getsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,&len_reuse);
printf("len_recv:%d\nlen_snd:%d reuse:%d\n",recv_size,snd_size ,reuse);

return 0;
}
