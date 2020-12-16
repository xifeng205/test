/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-25 16:28
 * Last modified : 2020-09-25 16:28
 * Filename      : sync.cpp
 * Description   :
 *********************************************************************/

#include <error.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;
#define test
#if defined test1
int ticket_nums = 20;

void *sell_ticket(void *) {
  for (int i = 0; i < ticket_nums; ++i) {
    if (ticket_nums) {
      cout << "Sell the ticket num is " << i << endl;
    }
    ticket_nums--;
  }
  return (void *)0;
}
int main(int argc, char **argv) {
  pthread_t tid[4];
  int ret;
  for (int i = 0; i < 4; ++i) {
    ret = pthread_create(&tid[i], NULL, sell_ticket, NULL);
    if (ret) {
      cout << "creat sell_ticket " << i << "error." << endl;
      return 1;
    }
  }
  void *status[4];
  for (int i = 0; i < ticket_nums; ++i) {
    ret = pthread_join(tid[i], &status[i]);
    if (ret) {
      cout << "pthread_join error. " << endl;
      return 1;
    }
  }
  return 0;
}
//多线程同步:
//同步指的是在一一定时间内只有某一个线程访问某个资源
//线程同步的常见方法: (1) 互斥锁, (2) 条件变量, (3) 读写锁 (4) 信号量
#elif defined test2
//互斥锁: 本质上是一种特殊的全局变量. 拥有lock 和unlock 状态. unlock状态的
//互斥锁的初始化分为动态初始化和静态初始化:
//(1) pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//(2) pthread_mutex_init()
//
//互斥锁的相关属性及其分类
//(1) 初始化互斥锁属性: pthread_mutexattr_init(phread_mutexattr_t attr);
//(2) 销毁互斥锁属性: pthread_mutexattr_destory(phread_mutexattr_t attr);
//(3) 获取互斥锁属性: int pthread_mutexattr_getpshared(pthread_mutexattr_t
//*restrict
//                    attr, int *restrict pshared);
//(4) 设置互斥锁属性: int pthread_mutexattr_setpshared(phread_mutexattr_t *attr,
// int pshared) ;
// attr 表示互斥锁的属性,
// pthread 表示互斥锁的共享属性, 有两种取值
// (1) PTHREAD_PROCESS_PRIVATE: 锁只能用于同一进程的两个线程.
// (1) PTHREAD_PROCESS_SHARED: 锁可以用于不同进程中的线程进行互斥,
// 同时还需要在进程共享内存中 分派互斥锁, 然后为该互斥锁指定属性就可以.

//获取互斥锁类型:int phread_mutexattr_gettype(const phread_mutexattr_t *restrict
// attr, int *restrict type) 设置互斥锁类型:int phread_mutexattr_settype(const
// phread_mutexattr_t *restrict attr, int type) 参数type 表示互斥锁的类型,
//总共由四种类型:(1) j 参数type表示互斥锁的类型，总共有以下四种类型：
// 1.PTHREAD_MUTEX_NOMAL:标准互斥锁，第一次上锁成功，第二次上锁会失败并阻塞
// 2.PTHREAD_MUTEX_RECURSIVE:递归互斥锁，第一次上锁成功，第二次上锁还是会成功，
// 可以理解为内部有一个计数器，每加一次锁计数器加1，解锁减1
// 3.PTHREAD_MUTEX_ERRORCHECK:检查互斥锁，第一次上锁会成功，第二次上锁出错返回错误信息，
// 不会阻塞
// 4.PTHREAD_MUTEX_DEFAULT:默认互斥锁，第一次上锁会成功，第二次上锁会失败

int ticket_nums = 20;

pthread_mutex_t mutex;
void *sell_ticket(void *) {
  for (int i = 0; i < ticket_nums; ++i) {

    pthread_mutex_lock(&mutex);
    if (ticket_nums) {
      cout << "Sell the ticket num is " << i << endl;
    }
    ticket_nums--;
    pthread_mutex_unlock(&mutex);
  }
  return (void *)0;
}
int main(int argc, char **argv) {
  pthread_t tid[4];
  int ret;
  pthread_mutex_init(&mutex, NULL);
  for (int i = 0; i < 4; ++i) {
    ret = pthread_create(&tid[i], NULL, sell_ticket, NULL);
    if (ret) {
      cout << "creat sell_ticket " << i << "error." << endl;
      return 1;
    }
  }
  void *status[4];
  for (int i = 0; i < ticket_nums; ++i) {
    ret = pthread_join(tid[i], &status[i]);
    if (ret) {
      cout << "pthread_join error. " << endl;
      return 1;
    }
  }
  return 0;
}
#elif defined test3
//条件变量:互斥量不是万能的, 比如某个线程正在等待共享数据的某个条件出现,
//可能需要对数据重复进行加锁和解锁,
//条件变量的相关函数:
//(1) 静态创建: phread_cond_t cond = PTHREAD_COND_INIIIALIZER;
//(2) 动态创建: int phtead_cond_init(&cond, NULL);
//(3) 销毁: int pthread_cond_destory(&cond);
//(4) conditon wait: int pthread_cond_wait(&cond, &mutex);
//(5) time wait: int pthread_cond_timewait(&cond, &mutex, time);
//(6) 激活一个等到线程: int phtead_cond_signal(&cond);
//(7) 激活所有等到线程: int pthread_cond_broadcast(&cond);
// phread_cond_singal() 会根据等到线程的优先级和等待时间来确定激发那一个线程.
pthread_cond_t cond;
pthread_mutex_t mutex;

int travel_nums = 0;
void *traveler_arrive(void *name) {
  cout << (char *)name << "need a teci, now" << endl;
  pthread_mutex_lock(&mutex);
  travel_nums++;
  pthread_cond_wait(&cond, &mutex);
  cout << "The traveler has leaved" << endl;
  pthread_mutex_unlock(&mutex);
  return (void *)0;
}

void *taxi_arrive(void *) {
  cout << "The texi arrives\n\r" << endl;
  while (1) {
    pthread_mutex_lock(&mutex);
    if (travel_nums) {
      pthread_cond_signal(&cond);
      cout << "The texi has leaved" << endl;
      pthread_mutex_unlock(&mutex);
      break;
    }
    pthread_mutex_unlock(&mutex);
  }
  travel_nums--;
  pthread_exit((void *)0);
}

int main(int argc, char **argv) {
  pthread_t tid_traveler, tid_texi;
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
  int ret;
  ret = pthread_create(&tid_traveler, NULL, traveler_arrive, (void *)"jeck");
  if (ret) {
    perror("Create tid_traveler thread error.\n\r");
  }
  sleep(1);
  ret = pthread_create(&tid_texi, NULL, taxi_arrive, (void *)"mike");
  if (ret) {
    perror("Create tid_texi thread error.\n\r");
  }
  sleep(1);
  ret = pthread_join(tid_texi, NULL);
  if (ret) {
    perror("Tid_texi join err.\n\r");
  }
  ret = pthread_join(tid_traveler, NULL);
  if (ret) {
    perror("Tid_traveler join err.\n\r");
  }
  return 0;
}
#elif defined test3
//读写锁: 可以对多个线程同时进行读, 但是不能进行同时写
int main(int argc, char **argv) { return 0; }
#elif defined test
//信号量:信号量和互斥锁的却别, 互斥锁允许一个线程进入临界区, 而信号来量
//允许多个线程进入临界区
//(1) 信号量的区别: int sem_init(&sem, psharead, v);
//    pshared 为0表示信号量为当前进程的局部信号量
//    pshared 为1表示信号量可以在多个进程之间共享
//    v为信号量的初始值
//    成功返回0, 失败时返回-1
//
//(2) 信号值的加减
//    int sem_wait(&sem); 以原子的方式将信号量的值减1
//    int sem_post(&sem); 以原子的方式将信号量的值加1
//(3) 信号量的值销毁
//    int sem_destory(&sem);
//通过信号量模拟两个窗口, 10个客人进行服务的过程
//
int nums = 10;
sem_t sem;

void *get_severce(void *cid) {
  int id = *(int *)cid;
  if (!sem_wait(&sem)) {
    sleep(5);
    cout << "Custom " << id << "get service" << endl;
    cout << "Custom " << id << "done" << endl;
    sem_post(&sem);
  }
  return (void *)0;
}

int main(int argc, char **argv) {
  pthread_t tid[10];
  sem_init(&sem, 0, 2);
  int id;
  for (int i = 0; i < nums; ++i) {
    id = i;
    int ret = pthread_create(&tid[i], NULL, get_severce, &id);
    if (ret) {
      cout << "Create thread " << tid[i] << "error." << endl;
      return -1;
    }
  }
  for (int i = 0; i < nums; ++i) {
    int ret = pthread_join(tid[i], NULL);
    if (ret) {
      cout << "Pthread join " << tid[i] << "error" << endl;
      return -1;
    }
  }
  sem_destroy(&sem);
  return 0;
}
#endif
