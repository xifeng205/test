/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 10:52
 * Last modified : 2020-08-19 10:52
 * Filename      : overbound.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
  char a;
  char *str = &a;
  strcpy(str, "hellow");
  std::cout << str << std::endl;
 return 0;
}
