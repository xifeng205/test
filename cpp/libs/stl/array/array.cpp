/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-03 16:33
 * Last modified : 2020-08-03 16:33
 * Filename      : array.cpp
 * Description   :
 *********************************************************************/

#include <array>
#include <iostream>

using namespace std;
#define TEST3
#if defined TEST0
int main(int argc, char **argv) {
    array<int, 38> dou;
    array<int, 10> arr{};
    cout << arr.size() << std::endl;
    cout << arr.max_size() << std::endl;
    return 0;
}
#elif defined TEST1
int main(int argc, char **argv) {
  array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  cout << arr.size() << std::endl;
  cout << arr.max_size() << std::endl;
  for (auto i = arr.begin(); i != arr.end(); ++i)
    std::cout << *i;
  std::cout << std::endl;
  for (auto i = arr.rbegin(); i != arr.rend(); ++i)
    std::cout << *i;
  std::cout << std::endl;
  for (auto i = arr.crbegin(); i != arr.crend(); ++i)
    std::cout << *i;
  std::cout << std::endl;
  return 0;
}
#elif defined TEST2
int main(int argc, char **argv) {
  array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  for (int i = 0; i < arr.size(); ++i)
    std::cout << arr.at(i);

  std::cout << std::endl;
  std::cout << get<2>(arr) << std::endl;
  return 0;
}
#elif defined TEST3
int main(int argc, char **argv) {
    array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::cout << arr.front() << std::endl;
    std::cout << arr.back() << std::endl;

    arr.fill(9);
    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr.at(i);
    std::cout << std::endl;
    array<int, 10> arr1{};
    arr.swap(arr1);
    for (int i = 0; i < arr1.size(); ++i)
        std::cout << arr1.at(i);
    std::cout << std::endl;

    return 0;
}
#endif
