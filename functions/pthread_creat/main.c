#include<stdio.h>
#include<pthread.h>

void *testThrFxn(void)
{
    printf("this only is a test\n\r");
}

int main(int argc, char **argv)
{
    pthread_t tid;
    pthread_craete(&tid, NULL, testThrFxn, NULL);
    /* pthread_join(&tid); */

}
