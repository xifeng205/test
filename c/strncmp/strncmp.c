/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-09-09 14:09
 * Last modified : 2020-09-09 14:09
 * Filename      : strncmp.cpp
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
  char s1[10] = "12347888";
  char s2[10] = "123433333";
  printf("%d", strncmp(s1, s2, 5));
  return 0;
}
