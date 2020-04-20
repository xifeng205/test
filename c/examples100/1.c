/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-25 09:44
 * Last modified : 2020-03-25 09:44
 * Filename      : 1.c
 * Description   : 
*********************************************************************/
#include <stdio.h>

int main(char argc, char **argv)
{
    int k, j , i;

    for (k = 1; k < 5; k++)
    {
        for (j = 1; j < 5; j++)
        {
            for (i = 1; i < 5; i++)
            {
                if (k != j && k != i && j != i)
                {
                    printf("%d%d%d\n", i, j ,k );
                }
            }
        }
    }
}
