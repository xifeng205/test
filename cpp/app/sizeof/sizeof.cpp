/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-11 21:22
 * Last modified : 2020-08-11 21:22
 * Filename      : sizeof.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

typedef struct test{
char a;
void *p;
} test;
int main(int argc, char **argv) {
  // char str[] = "http://www.ibegroup.com/";
  // std::cout << sizeof(str) << std::endl;
  cout << sizeof(test)<<endl;
 return 0;
}
