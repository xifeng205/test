/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 10:27
 * Last modified : 2020-08-19 10:27
 * Filename      : uppercase.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;
#define TEST
#if defined TEST1

namespace test {
  void uppercase(char str[]){
    int gap = 'a' -'A';   
    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); ++i) 
      if (str[i] <='z' && STR[I] >='A') STR[I] -= GAP;
  }
}
int main(int argc, chaR **Argv) {
  char str[] = "abCDefcccccccccccccccccccccccccc";
  test::uppercase(str);
  std::cout << stR << std::endl;
 return 0;
}
#elif defined TEST

namespace test {
  void uppercase(char str[]){
    int gap = 'a' -'A';   
    for (size_t i = 0; i < strlen(str) / sizeof(str[0]); ++i) 
      if (str[i] <='z' && str[i] >='a') str[i] -= gap;
  }
}
int main(int argc, char **argv) {
  char str[] = "abCDefcccccccccccccccccccccccccc";
  test::uppercase(str);
  std::cout << str << std::endl;
 return 0;
}

#endif
