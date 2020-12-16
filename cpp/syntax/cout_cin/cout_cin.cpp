/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-21 17:43
 * Last modified : 2020-08-21 17:43
 * Filename      : cout_cin.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {
  std::cout << std::hex << 18 << std::endl;
  std::cout << 78 << std::endl;
  std::cout << std::oct << 18 << std::endl;
  std::cout << std::dec << 18 << std::endl;
  std::cout << std::setw(12)<< std::setfill('-') << 18 << std::endl;
  std::cout << std::resetiosflags(ios::basefield) << std::endl;
  std::cout << std::dec << 18 << std::endl;
 return 0;
}
