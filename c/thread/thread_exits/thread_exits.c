#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *create(void *arg) {
  printf("New thread is created ...\n"); 
  return (void *)8;
}
int main(int argc, char **argv) {
    pthread_t tid;
    int ret;
    void *temp;
    ret = pthread_create(&tid, NULL, create, NULL);
    printf("Main thread.");
    if(ret)
    {
      printf("thread is not created ...\n");
      return -1; 
    }
    ret = pthread_join(tid, &temp);
    if(ret){
      printf("thread is not exist ...\n");
      return -2;
    }
}



