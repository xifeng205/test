/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-21 15:00
 * Last modified : 2020-08-21 15:00
 * Filename      : str2l.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace test {

  long str2long(char *str, long &intg) {
    intg = 0;
    while (*str !='\0') {
      intg = intg * 10 + (*str - '0');
      ++str;
    }
    return intg;
  } 
}
int main(int argc, char **argv) {
  char str[] = "1235";
  long val;
  test::str2long(str, val);
  std::cout << val << std::endl;

 return 0;
}
