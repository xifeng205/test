/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-21 14:51
 * Last modified : 2020-07-21 14:51
 * Filename      : arry_local.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <string.h>
char *a = "hellow world.";
void get_array() {
    static char b[20] = {0};
    memcpy(b, a, strlen(a));
    printf("%s", b);
}
int main(int argc, char **argv)
{
    get_array(); 
    return 0;
}
