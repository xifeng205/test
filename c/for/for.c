/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-17 12:52
 * Last modified : 2020-03-17 12:52
 * Filename      : for.c
 * Description   : 
*********************************************************************/
#include <stdio.h>

int main(int argc, char **argv)
{
    int i;
    for(i = 0; i < 5; ++i)
    {
        printf("%d", i);
    }

    printf("\n");

    for(i = 0; i < 5; i++)
    {
        printf("%d", i);
    }
}
