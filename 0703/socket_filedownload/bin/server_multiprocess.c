/*************************************************************************
	> File Name: server.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 03 Jul 2014 10:02:48 AM CST
 ************************************************************************/
#include "my_socket.h"
#include <signal.h>
#include <errno.h>
void sig_handle(int num)
{
	while(waitpid(-1, NULL, WNOHANG) > 0) ;
}
int main(int argc , char* argv[])//exe ip port
{
	signal(13,SIG_IGN);
	signal(17,sig_handle);
	if(argc != 3)
	{
		printf("usge : exe ip port");
		exit(-1);
	}
	int fd_server ,fd_client;
	struct sockaddr_in client_addr ;
	int addrlen = sizeof(client_addr);
	fd_server = listenfd_init(argv[1],argv[2]);
	while( (fd_client = accept(fd_server,(struct sockaddr*)&client_addr,&addrlen) ) > 0 )
	{
		if(fd_client == -1)
		{
			if(errno == EINTR)
			{
				continue ;
			}
		}
		printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		if(fork() == 0)
		{
			close(fd_server);
			handle_request(fd_client);
			exit(0);
		}
	}

}
server_addr, 0 , sizeof(server_addr)) ;
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(-1 == bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	if(-1 == listen(fd_server,5))
	{
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	while(fd_client = accept(fd_server,(struct sockaddr*)&client_addr,&addrlen))
	{
		printf("a client connect :%s:%d\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		memset(&msg,0, sizeof(msg));
		recv(fd_client,&msg, MSG_LEN , 0) ;
		recv(fd_client,&msg.s_buf,msg.s_len,0) ;
		printf("recv msg :%s \n", msg.s_buf);
		fd_file = open(msg.s_buf,O_RDONLY);
		while(memset(&snd_msg,0,sizeof(msg)), (read_n = read(fd_file,snd_msg.s_buf,MSG_SIZE)) > 0)
		{
			snd_msg.s_len = read_n ;
			send(fd_client, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
		}
		snd_msg.s_len = 0 ;
		send(fd_client, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
		close(fd_file);
		close(fd_client);
	
	}

}
