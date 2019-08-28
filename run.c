#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/wait.h>
int main(void)
{
	int pid,status;
	pid=fork();
	if(pid>0)
	{
		wait(&status);
		execl("out",(char *)0);
	}
	else if(pid==0)
	{
		execl("/bin/gcc","gcc","shell.c","-o","out",(char *)0);
		exit(EXIT_SUCCESS);
	}
}



