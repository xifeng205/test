/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-21 13:42
 * Last modified : 2020-08-21 13:42
 * Filename      : calc_age.cpp
 * Description   : 
*********************************************************************/
//  一人岁数的3次方是四位数，四次方是六位数，并知道此人岁数的3次方和4次方用遍了0～9十个数字。编写一程序求此人的岁数。
#include <iostream>

#define TEST
#if defined TEST
namespace test {
   int get_age(int age_limit) {
     char age_str[11];
     long  age_3, age_4;
     for (int age = 0; age < age_limit; ++age) {
       age_3 = age * age *age;
       age_4 = age * age *age * age;
       if ( age_3 > 1000 && age_3 < 9999 && age_4 > 100000 && age_4 < 999999) {
          for (int i = 0; i < 4; ++i) {
            age_str[i] = age_3%10; 
            age_3 = age_3 / 10;
          }
          for (int i = 4; i < 10; ++i) {
            age_str[i] = age_4%10; 
            age_4 = age_4 / 10;
          }
          for (int i = 0; i < 11; ++i) {
            for (int j = 1; j < 11 - i+1; ++i) 
              if (age_str[i] == age_str[j]) break;
              if (i == 11) return age;
          } 
       }
     }
     return -1;
   } 
}
using namespace std;

int main(int argc, char **argv) {
  int age = test::get_age(100);
  std::cout << age << std::endl;
  return 0;
}

#endif
// 对1，2，3， 4， 5 这五个数任意取出两个数，列出他们的所有组合。
