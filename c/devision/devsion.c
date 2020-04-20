/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-03 16:54
 * Last modified : 2020-04-03 16:54
 * Filename      : devsion.c
 * Description   : 
 *********************************************************************/

#include <stdio.h>

int main(int argc, char **argv)
{
    for (int i = 0; i < 6; i++) {
        int j = (i + 1)*7/3 - i*7/3;
        printf("j = %d\n", j);
    }
    /* printf("%d\n", 3/2); */
    /* printf("%d\n", 4/3); */
    /* printf("%d\n", 9/5); */


    return 0;
}
