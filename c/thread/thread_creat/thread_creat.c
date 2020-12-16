#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void *mythread1(void) {
  for (int i = 0; i < 100; ++i) {
    printf("This is the 1st phtead\n\r");
    sleep(1);
  }
}

void *mythread2(void) {
  for (int i = 0; i < 100; ++i) {
    printf("This is the 2st thread\n\r");
    sleep(1);
  }
}
int main() {
  int i = 0, ret = 0;
  pthread_t id1, id2;
  ret = pthread_create(&id1, NULL, (void *)mythread1, NULL);
  if(ret)
  {
    printf("Create pthread error.\n");
    return 1;
  }

  ret = pthread_create(&id1, NULL, (void *)mythread2, NULL);
  if(ret){
    return printf("Create thread2 error.\n");
    return 1;
  }
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
  return 0;
}
