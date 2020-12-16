/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-19 14:29
 * Last modified : 2020-08-19 14:29
 * Filename      : test84.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <cstring>
using namespace std;
#define TEST
#if defined TEST1
namespace test {
   void get_memory(char *str) {
      str = (char *)malloc(sizeof(char) * 100); 
   } 

}
int main(int argc, char **argv) {
  char *str = nullptr;
  test::get_memory(str);
  strcpy(str, "helow");
  std::cout << str << std::endl; 
  free(str);
  return 0;
}
#elif defined TEST2

namespace test {
   void get_memory(char **str) {
      *str = (char *)malloc(sizeof(char) * 100); 
   } 
}
int main(int argc, char **argv) {
  char *str = nullptr;
  test::get_memory(&str);
  strcpy(str, "helow");
  std::cout << str << std::endl; 
  free(str);
  return 0;
}
#elif defined TEST

namespace test {
   char *get_memory(char *str) {
      str = (char *)malloc(sizeof(char) * 100); 
      return str;
   } 
}
int main(int argc, char **argv) {
  char *str = nullptr;
  str = test::get_memory(str);
  strcpy(str, "helow");
  std::cout << str << std::endl; 
  free(str);
  return 0;
}

#endif
