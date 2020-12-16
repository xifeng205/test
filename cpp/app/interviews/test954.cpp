/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 18:22
 * Last modified : 2020-08-19 18:22
 * Filename      : test954.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {
   void swap(int &x, int &y) {
      x = x + y; 
      y = x - y;
      x = x - y;
   } 
}
int main(int argc, char **argv) {
int a= 10, b = 11;

test::swap(a, b);
std::cout << a << std::endl;
std::cout << b << std::endl;
 return 0;
}
