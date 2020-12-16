/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-01 22:03
 * Last modified : 2020-07-01 22:03
 * Filename      : thread_local.cpp
 * Description   : 
*********************************************************************/
// thread_local.cpp
#include <iostream>
#include <thread>

class A {
public:
  A() {
    std::cout << std::this_thread::get_id()
              << " " << __FUNCTION__
              << "(" << (void *)this << ")"
              << std::endl;
  }

  ~A() {
    std::cout << std::this_thread::get_id()
              << " " << __FUNCTION__
              << "(" << (void *)this << ")"
              << std::endl;
  }

  // 线程中，第一次使用前初始化
  void doSth() {
  }
};

thread_local A a;

int main() {
  a.doSth();
  std::thread t([]() {
    std::cout << "Thread: "
              << std::this_thread::get_id()
              << " entered" << std::endl;
    a.doSth();
  });

  t.join();

  return 0;
}

