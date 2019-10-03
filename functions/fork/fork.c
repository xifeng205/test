#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

/* ���̴��� */
void main(void)
{
	pid_t child;
	int status;

	printf("This will demostrate how to get child status\n");

	/* �����ӽ��� */
	if((child=fork())==-1)
	{
		printf("Fork Error : %s\n", strerror(errno));
		exit(1);
	}
	else if(child==0) // �ӽ���
	{
		int i;
		printf("I am the child: %s\n", getpid());
		for(i=0;i<1000000;i++) sin(i);
		i=5;
		printf("I exit with %d\n", i);
		exit(i);
	}

	while(((child=wait(&status))==-1)&(errno==EINTR));  //�ӽ���δ����

	if(child==-1)
		printf("Wait Error: %s\n", strerror(errno));
	else if(!status)             // �ӽ����˳�ֵΪ0
		printf("Child %ld terminated normally return status is zero\n", child);
	else if(WIFEXITED(status))   // �ӽ����˳�ֵ0
		printf("Child %ld terminated normally return status is %d\n", child, WEXITSTATUS(status));
	else if(WIFSIGNALED(status)) // �ӽ���δ���źŶ��˳�
		printf("Chlid %ld terminated due to signal %d not caught\n", child, WTERMSIG(status));
}	
