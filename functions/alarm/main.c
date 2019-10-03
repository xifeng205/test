#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>


void sig_alarm(int sig)
{
    printf("----%d", sig);
}
int main ()
{
    /* signal(SIGALRM, sig_alarm); */
    alarm(5);
    printf("1111111111\n");
    sleep(20);
    printf("end!\n");
    return 0;
}
