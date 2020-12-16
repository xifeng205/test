#include <pthread.h>
#include <unistd.h>

void *thread(void *str){
  int i;
  for(i= 0; i< 10; ++i)
  {
    printf("this in the thread : %d\n", i);
    sleep(2);
  }
  return NULL;
}
int main(int argc, char **argv) {
  pthread_t pid;
  int i;
  int ret = pthread_create(&pid, NULL, thread, NULL);
  if(ret) {
    printf("Create thread pid error.\n"); 
  }
  pthread_join(pid, NULL);
  for(int i = 0; i < 10; ++i) {
     printf("Main thread i is %d .\n", i);  
  }
  return 0;
}
