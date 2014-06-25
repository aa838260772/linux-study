/*************************************************************************
  > File Name: my_shell.c
  > Author: One
  > Mail:838260772@qq.com 
  > Created Time: 2014年06月25日 星期三 18时42分15秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define TITLE  "sjswj@local ~:"
#define MAX_LEN  256

int main()
{
	pid_t iret;
	char str[MAX_LEN];
	char **arglist;
	int i,j,k,sign;
	char path[256];
	while(1)
	{
		i=j=k=sign=0;
		arglist=NULL;
		printf("%s",TITLE);
		memset(str,0,sizeof(str));
		//sprintf(str,"%s","ls -l");
		if(fgets(str,sizeof(str),stdin)&&str[0]!='\n')
		//if(str[0]!='\n')
		{
			while(str[j]!='\n')
			{
				if(sign==0&&str[j]!=' ')
					k++;
				if(str[j]==' ')
					sign=0;
				else
					sign=1;
				j++;
			}

			arglist=(char**)malloc((k+1)*sizeof(char*));
			j=0;
			sign=0;

			while(str[j]!='\n')
			{
				if(sign==0&&str[j]!=' ')
					*(arglist+i++)=&str[j];
				if(str[j]==' ')
				{
					str[j]='\0';
					sign=0;
				}
				else
					sign=1;
				j++;
			}		
			str[j]='\0';
			*(arglist+i)=NULL;

			memset(path,0,256);
			sprintf(path,"%s","/bin/");
			strcat(path,arglist[0]);
			iret=fork();
			if(iret==0)
			{
				execvp(path,arglist+1);
			//	exit(-1);
			}
			else
			{
				wait(NULL);
			//	exit(-1);
			}
		}
	}
	return 0;
}

