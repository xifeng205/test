/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-03 14:55
 * Last modified : 2020-11-03 14:55
 * Filename      : scanf.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  char line[50]  ={"helldofi 190"};
  char a[10];
  int b;
  sscanf(line, "%s%d",a, &b); 
  cout << a  << " " << b << std::endl;
  return 0;
}
