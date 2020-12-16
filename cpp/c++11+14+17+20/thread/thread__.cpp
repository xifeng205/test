/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-08 09:51
 * Last modified : 2020-08-08 09:51
 * Filename      : thread.cpp
 * Description   :
 *********************************************************************/
/*
 * std::thread
 * 用于创建一个执行的线程实例，所以它是一切并发编程的基础，使用时需要包含头文件
 * ，它提供了很多基本的线程操作，例如get_id()来获取所创建线程的线程
 r ID，例如使用 join() 来加入一个线程等等，例如：
 */

#include <iostream>
#include <thread>
#include <sys/time.h>

using namespace std;
#define TEST1
#if defined TEST0
namespace thread_n {
void tfuc() { std::cout << "This only a test." << std::endl; }
} // namespace thread_n
int main(int argc, char **argv) {
  std::thread t(thread_n::tfuc);
  t.join();
  return 0;
}
#elif defined TEST1
#include <mutex>
namespace thread_n {

double get_times(char flag = 0) {
  static struct timeval tv_start;
  static struct timeval tv_end;
  long double times = 0;
  if (!flag) {
    gettimeofday(&tv_start, NULL);
  } else if (flag == 1) {
    gettimeofday(&tv_end, NULL);
    times = (tv_end.tv_usec - tv_start.tv_usec) +
            (tv_end.tv_sec - tv_end.tv_sec) * 10000 * 1000;
    std::cout << "Cost time: " << times << " us" << std::endl;
  } else if (flag == 2) {
    gettimeofday(&tv_end, NULL);
    times = static_cast<double>(tv_end.tv_usec - tv_start.tv_usec) / 1000 +
            (tv_end.tv_sec - tv_end.tv_sec) * 1000;
    std::cout << "Cost time: " << times << "ms" << std::endl;
  } else if (flag == 3) {
    gettimeofday(&tv_end, NULL);
    times = static_cast<double>(tv_end.tv_usec - tv_start.tv_usec) / 1000 / 1000 +
            (tv_end.tv_sec - tv_end.tv_sec);
    std::cout << "Cost time: " << times << " s" << std::endl;
  }
  return times;
}

/*
 *     们在操作系统的相关知识中已经了解过了有关并发技术的基本知识，mutex
 * 就是其中的核心之一。C++11 引入了 mutex 相关的类，其所有相关的函数都放在
 * <mutex> 头文件中。
 *
 * std::mutex 是 C++11 中最基本的 mutex 类，通过实例化 std::mutex
 * 可以创建互斥量，而通过其成员函数 lock() 可以仅此能上锁，unlock()
 * 可以进行解锁。但是在在实际编写代码的过程中，最好不去直接调用成员函数
 * ，因为调用成员函数就需要在每个临界区的出口处调用
 * unlock()，当然，还包括异常。这时候 C++11 还为互斥量提供了一个 RAII
 * 语法的模板类std::lock_gurad。RAII
 * 在不失代码简洁性的同时，很好的保证了代码的异常安全性。
 *
 * 在 RAII 用法下，对于临界区的互斥量的创建只需要在作用域的开始部分，例如：
 */
void func1() {
  static std::mutex mtx;
  std::lock_guard<std::mutex> guard_lock(mtx);
  cout << "Guard_lock test." << endl;
}
/*
 * 由于C++保证了所有栈对象在声明周期结束时会被销毁，所以这样的代码也是异常安全的
 * 无论 some_operation()正常返回、还是在中途抛出异常，都会引发堆栈回退，
 * 也就自动调用了 unlock(). 而 std::unique_lock 则相对于 std::lock_guard
 * 出现的， std::unique_lock 更加灵活，std::unique_lock
 * 的对象会以独占所有权（没有其他的 unique_lock 对象同时拥有某个 mutex
 * 对象的所有权）的方式管理 mutex 对象上的上锁
 * 和解锁的操作。所以在并发编程中，推荐使用 std::unique_lock。例如：
 */
void func2() {
  static std::mutex mtx;
  std::unique_lock<std::mutex> __unique_lock(mtx);
  cout << "Unique lock test." << endl;
}
}
int main(int argr, char **argv) {
  thread_n::get_times();
  std::thread t1(thread_n::func1);
  std::thread t2(thread_n::func2);
  t1.join();
  t2.join();
  thread_n::get_times(2);
  return 0;
}
#elif defined TEST2
#include <future>
#include <mutex>
/*
 * std::future
 * 则是提供了一个访问异步操作结果的途径，这句话很不好理解。为了理解这个特性，
 * 我们需要先理解一下在 C++ 11 之前的多线程行为。
 *
 * 试想，如果我们的主线程 A 希望新开辟一个线程 B
 * 去执行某个我们预期的任务，并返回我一个结果。而这时候，线程 A
 * 可能正在忙其他的事情，无暇顾及 B
 * 的结果，所以我们会很自然的希望能够在某个特定的时间获得线程 B 的结果。
 *
 * 在 C++11 的 std::future 被引入之前，通常的做法是：创建一个线程 A，在线程 A
 * 里启动任务
 * B，当准备完毕后发送一个事件，并将结果保存在全局变量中。而主函数线程 A
 * 里正在做其他的事情，当需要结果的时候，调用一个线程等待函数来获得执行的结果。
 *
 * 而 C++11 提供的 std::future
 * 简化了这个流程，可以用来获取异步任务的结果。自然地，
 * 我们很容易能够想象到把它作为一种简单的线程同步手段。
 *
 * 此外，std::packaged_task
 * 可以用来封装任何可以调用的目标，从而用于实现异步的调用。例如：
 */
int main(int argc, char **argv) {
  std::packaged_task<int()> task([]() { return 8; });
  std::future<int> result = task.get_future();
  std::thread t(std::move(task));
  t.detach();
  result.wait();
  std::cout << result.get() << std::endl;
  return 0;
}
/*
 * 在封装好要调用的目标后，可以使用 get_future() 来获得一个std::future对象，
 * 以便之后事实线程同步。
 */
#elif defined TEST3
/*
 * thread::condition_variable 是为了解决死锁而生的。当互斥操作不够用而引入的。
 * 比如，线程可能需要等待某个条件为真才能继续执行，而一个忙等待循环中可能会
 * 导致所有其他线程都无法进入临界区使得条件为真时，就会发生死锁。所以，
 * condition_variable 实例被创建出现主要就是用于唤醒等待线程从而避免死锁。
 * std::condition_variable的 notify_one() 用于唤醒一个线程；notify_all()
 * 则是通知所有线程。下面是一个生产者和消费者模型的例子：
 */
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int main() {
  // 生产者数量
  std::queue<int> produced_nums;
  // 互斥锁
  std::mutex m;
  // 条件变量
  std::condition_variable cond_var;
  // 结束标志
  bool done = false;
  // 通知标志
  bool notified = false;

  // 生产者线程
  std::thread producer([&]() {
    for (int i = 0; i < 5; ++i) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      // 创建互斥锁
      std::unique_lock<std::mutex> lock(m);
      std::cout << "producing " << i << '\n';
      produced_nums.push(i);
      notified = true;
      // 通知一个线程
      cond_var.notify_one();
    }
    done = true;
    cond_var.notify_one();
  });

  // 消费者线程
  std::thread consumer([&]() {
    std::unique_lock<std::mutex> lock(m);
    while (!done) {
      while (!notified) { // 循环避免虚假唤醒
        cond_var.wait(lock);
      }
      while (!produced_nums.empty()) {
        std::cout << "consuming " << produced_nums.front() << '\n';
        produced_nums.pop();
      }
      notified = false;
    }
  });

  producer.join();
  consumer.join();
  return 0;
}
#endif
