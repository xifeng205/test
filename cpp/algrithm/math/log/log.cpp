/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-10-23 10:26
 * Last modified : 2020-10-23 10:26
 * Filename      : log.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
  float ret = log(10);
  float r = exp(ret);
  std::cout << ret << std::endl;
  std::cout << r << std::endl;
  return 0;
}
