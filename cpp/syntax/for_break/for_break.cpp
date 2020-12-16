/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-21 14:38
 * Last modified : 2020-08-21 14:38
 * Filename      : for_break.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
//  for (int i = 0; i < 99; ++i) {
  // if ( i ==9 ) break;

  // std::cout << std::endl;
//  } 
for (int i = 0; i < 99; ++i) {
  if ( i ==9 ) continue;
   std::cout << i ;
  std::cout << std::endl;
 }
 return 0;
}
