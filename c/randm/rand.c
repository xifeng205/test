/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-03-31 23:13
 * Last modified : 2020-03-31 23:13
 * Filename      : rand.c
 * Description   : 
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int i;
    double j;
    srand(time(0));

    for(i=0;i<10;i++)
    {
    
      j= rand();
        /* j=rand() / (double)(RAND_MAX+2); */
        printf(" %f",j);
        /* j=rand() / (double)(RAND_MAX+0); */
        /* j=seed%10000; */
        /* printf(" %d",seed); */
        /* printf(" %f",j); */
    }
    return 0;
}
