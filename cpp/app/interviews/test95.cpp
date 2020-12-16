/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 16:33
 * Last modified : 2020-08-19 16:33
 * Filename      : test95.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {
  long factorial(int n) {
    if (n == 0 || n == 1) return 1;     
    return factorial(n-1)*n;
  }  
}
int main(int argc, char **argv) {
  long val = test::factorial(0);
  std::cout << val << std::endl;

  val = test::factorial(1);
  std::cout << val << std::endl;

  val = test::factorial(2);
  std::cout << val << std::endl;

  val = test::factorial(4);
  std::cout << val << std::endl;
 return 0;
}
