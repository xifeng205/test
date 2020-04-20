/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-02 22:00
 * Last modified : 2020-04-02 22:00
 * Filename      : gettimeofday.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <sys/time.h>

double what_time_is_it_now()
{
    struct timeval time;
    if (gettimeofday(&time, NULL)) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec *.000001;
}
    
int main(int argc, char **argv)
{
    double time = what_time_is_it_now();
    printf("the time is %f\n", time);
    return 0;
}
