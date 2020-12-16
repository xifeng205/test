/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-18 10:40
 * Last modified : 2020-07-18 10:40
 * Filename      : shared_ptr.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <memory>

using namespace std;
#define TEST0 
#if defined TEST1
int main(int argc, char **argv) {
  auto i = new int(10);
  std::cout << *i << std::endl;
  delete i;

  auto j = new int[10];

  for (int it = 0; it < 9; ++it)
    std::cout << j[it] << std::endl;
  delete[] j;

  std::shared_ptr<int> p1(new int(10));
  std::shared_ptr<int> p2 = p1;
  std::shared_ptr<int> p6(p2);
  std::shared_ptr<int> p3;
  std::shared_ptr<int> p4(nullptr);
  std::shared_ptr<int> p5 = make_shared<int>(10);
  std::cout << *p5 << std::endl;
  std::cout << p5.use_count() << std::endl;
  std::cout << p6.use_count() << std::endl;
  p6.reset();
  std::cout << p2.use_count() << std::endl;
  return 0;
}
#elif defined TEST1
int main(int argc, char **argv) {
 std::shared_ptr<int> p(new int(10)); 
 std::
 return 0;
}
#endif
