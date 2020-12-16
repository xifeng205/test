/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 17:39
 * Last modified : 2020-08-19 17:39
 * Filename      : test953.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {
  // 0, 1, 1, 2, 3, 5, 8, 13 ...
  int fabonaci(int n) {
    if (n == 0 ) return 0;
    if (n == 1 ) return 1;
    return fabonaci(n - 1) + fabonaci(n - 2);
  } 
}
int main(int argc, char **argv) {
  int ret = test::fabonaci(7);
  std::cout << ret << std::endl;
  return 0;
}
