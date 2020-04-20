/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-17 21:51
 * Last modified : 2020-04-17 21:51
 * Filename      : break.c
 * Description   : 
*********************************************************************/

#include <stdio.h>

int main(int argc, char **argv)
{
    for (int i = 0; i < 10; i++) {
        printf("i = %d\n", i);
        if (i == 3) break;
    }

   return 0;
}
