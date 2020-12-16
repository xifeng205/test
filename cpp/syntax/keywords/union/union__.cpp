/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-10 13:20
 * Last modified : 2020-08-10 13:20
 * Filename      : union__.cpp
 * Description   :
 *********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  typedef union test {
    char b;
    int a;
    double c;
  } test_u;
  test_u d = {10};
  std::cout << d.a << std::endl;
  std::cout << d.b << std::endl;
  std::cout << d.c << std::endl;
  return 0;
}
