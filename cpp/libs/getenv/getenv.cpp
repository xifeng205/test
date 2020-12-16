/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-08 22:14
 * Last modified : 2020-11-08 22:14
 * Filename      : getenv.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  char *s; 
  s = getenv("PATH");
  printf("%s\n", s);
  return 0;
}
