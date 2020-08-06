#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<wait.h>
int main(void)
{
	char ch[20],ch1[20],pwd[100];
	for(int i=0;i<100;i++)
		pwd[i]=' ';
	int f,pid,status;
start:
	printf("1. The list of available commands can be viewed by typing \"man \\ \" \n");
	printf("2. Any command which doesn't require an input should be provided an input \"\\\" \n");
	printf("For e.g. : ls should be written as \"ls \\ \" \n");
	printf("myshell>");
	scanf("%s%s",ch,ch1);
	if(strcmp(ch,"ls")==0)
		f=1;
	else if(strcmp(ch,"pwd")==0)
		f=2;
	else if(strcmp(ch,"mkdir")==0)
                f=3;
	else if(strcmp(ch,"exit")==0)
		f=-1;
	else if(strcmp(ch,"cd")==0)
                f=4;
	else if(strcmp(ch,"rmdir")==0)
		f=5;
	else if(strcmp(ch,"man")==0)
		f=6;
	else
		f=0;
	if(f==-1)
		exit(0);
	pid=fork();
	if(pid==0)
switch(f)
{
	case 1:
		{
			int nd=0;
				DIR *p;
				struct dirent *d1;
				char ch[100];
				getcwd(ch,100);
				p= opendir(ch);
				if(p==NULL)
				{
					perror("can not find directory");
					exit(-1);
				}
				while(d1=readdir(p))
				{
					printf("%s\t\t\t",d1->d_name);
				nd++;
				if(nd%3==0)
					printf("\n");
				}
				exit(0);
		}
		case 2:
                {
				char ch[100];
				if(!getcwd(ch,100))
				{
					perror("ERROR");
					exit(EXIT_FAILURE);
				}
				else
					printf("%s\n",ch);
				exit(0);
		}
		case 3:
                {
				char cwd[100];
				if(!getcwd(cwd,100))
				{
					perror("ERROR");
					exit(EXIT_FAILURE);
				}
				strcat(cwd,"/");
				strcat(cwd,ch1);
				if(mkdir(cwd,0777)==-1)
				{
					perror("ERROR");
					exit(EXIT_FAILURE);
				}
                        exit(0);
		}
		case 4:
                {
				char ch[100];
				int k;
				k=chdir(ch1);
				if(k==-1)
				{
					perror("ERROR");
					exit(EXIT_FAILURE);
				}
				getcwd(ch,100);
				printf("%s\n",ch);
				exit(0);
		}
		case 5:
                {
			char ch[100];
			if(!getcwd(ch,100))
			{
				perror("ERROR");
				exit(EXIT_FAILURE);
			}
			strcat(ch,"/");
			strcat(ch,ch1);
			rmdir(ch);
			exit(0);
		}
		case 6:
                {
                                printf("1.ls\n");
				printf("2.cd\n");
				printf("3.pwd\n");
				printf("4.mkdir\n");
				printf("5.rmdir\n");
				printf("6.man\n");
				printf("7.exit\n");
                                exit(0);
		}
		default:
		{
			printf("%s is not recognized.\n",ch);
			exit(0);
		}
}
else if(pid>0)
{
	wait(&status);
	goto start;
}
}
