/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-25 15:27
 * Last modified : 2020-08-25 15:27
 * Filename      : cahr.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include<iomanip>

using namespace std;

int main(int argc, char **argv) {
  unsigned char a = 255;
  std::cout << hex << a << std::endl;
  a++;
  std::cout << a << std::endl;
  a++;
  std::cout << a << std::endl;
 return 0;
}
