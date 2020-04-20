/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-30 09:52
 * Last modified : 2020-03-30 09:52
 * Filename      : for.c
 * Description   : 
 *********************************************************************/
#include <stdio.h>

int main(int argc, char **argv)
{
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        printf("the i is %d\n", i);
    }
    return 0;
}
