/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-25 10:44
 * Last modified : 2020-08-25 10:44
 * Filename      : fuc_object.cpp
 * Description   :
 *********************************************************************/
//如果一个类将括号()运算符重载为成员函数, 则这个类就是函数对象类,
//这个类的对象就是函数对象, 函数对象是一个对象, 但是使用形式上像函数调用,
//实际上也执行了函数调用.
#include <iostream>
#include <vector>

using namespace std;
#define TEST
#if defined TEST0
class caverage {
public:
  double operator()(int a, int b, int c) { return (a + b + c) / 3; }
};
int main(int argc, char **argv) {
  caverage average;
  int a = 1;
  int b = 22;
  int c = 3;
  double d = average(a, b, c);
  std::cout << d << std::endl;
  return 0;
}
#elif defined TEST
namespace num {
template <class InIt, class T, class pred>
T accumulate(InIt first, InIt last, T init, pred op) {
  for (; first != last; ++first) {
    init = op(init, *first);
  }
  return init;
}
class acc {
public:
  int operator()(int a, int b) { return a + b; }
};
int add(int a, int b) {
  return a + b;
}
} // namespace num
//函数对象在accumulate 中的应用
int main(int argc, char **argv) {
  num::acc accs;
  std::vector<int> vec{1, 3, 4, 5, 6, 7, 8};
  std::vector<int>::const_iterator it_beg = std::cbegin(vec);
  std::vector<int>::const_iterator it_end = std::cend(vec);
  int total = 0;
  total = num::accumulate(it_beg, it_end, total, accs);
  std::cout << total << std::endl;
  return 0;
}
#endif
