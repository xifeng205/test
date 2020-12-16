/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-08 19:54
 * Last modified : 2020-11-08 19:54
 * Filename      : locale.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <locale>

using namespace std;

int main() {
  wchar_t ss[20];   
  char *p;
  p = setlocale(LC_ALL, "");

  ss[0] =L'中';
  ss[1] = L'文';
  ss[2] = L'\0';

  wprintf(L"%1s", ss);
  // printf("地域设置:%s\n", p);

  return 0;
}
