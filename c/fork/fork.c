#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

/* 进程创建 */
void main(void)
{
	pid_t child;
	int status;

	printf("This will demostrate how to get child status\n");

	/* 创建子进程 */
	if((child=fork())==-1)
	{
		printf("Fork Error : %s\n", strerror(errno));
		exit(1);
	}
	else if(child==0) // 子进程
	{
		int i;
		printf("I am the child: %s\n", getpid());
		for(i=0;i<1000000;i++) sin(i);
		i=5;
		printf("I exit with %d\n", i);
		exit(i);
	}

	while(((child=wait(&status))==-1)&(errno==EINTR));  //子进程未结束

	if(child==-1)
		printf("Wait Error: %s\n", strerror(errno));
	else if(!status)             // 子进程退出值为0
		printf("Child %ld terminated normally return status is zero\n", child);
	else if(WIFEXITED(status))   // 子进程退出值0
		printf("Child %ld terminated normally return status is %d\n", child, WEXITSTATUS(status));
	else if(WIFSIGNALED(status)) // 子进程未获信号而退出
		printf("Chlid %ld terminated due to signal %d not caught\n", child, WTERMSIG(status));
}	
