/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-11-09 16:01
 * Last modified : 2020-11-09 16:01
 * Filename      : strncpy.c
 * Description   : 
*********************************************************************/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char ss[10] = "djfsd";
  char dst[11];
  strncpy(dst, ss, strlen(ss));
  printf("%s", dst);
}
