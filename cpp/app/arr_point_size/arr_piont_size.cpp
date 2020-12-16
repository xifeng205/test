/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-14 15:23
 * Last modified : 2020-08-14 15:23
 * Filename      : arr_piont_size.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  int arr[10];
  std::cout << sizeof(arr) << std::endl;
  typedef struct test {
      int a;
      int b;
      char *c;
  } test;
  test __test;
  std::cout << sizeof(test) << std::endl;
  // char *str ="helliidifiiow";
  // std::cout << sizeof(str) << std::endl;
  char (*a)[10];
  std::cout << sizeof(a)<< std::endl;
  char *b[3];
  cout << sizeof(b)<< endl;
  return 0;
}
