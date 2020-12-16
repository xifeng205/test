/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-30 17:26
 * Last modified : 2020-07-30 17:26
 * Filename      : time.cpp
 * Description   : 
*********************************************************************/
#include <exception>
#include <iostream>
#include <ctime>
#include <sys/time.h>

using namespace std;
// #define CLOCK
// #define TIME
// #define ASCTIME
#define MAKE_TIME
#if defined CLOCK
int main(int argc, char **argv)
{
    clock_t clk_start = clock();
    for (int i=0; i < 100; ++i) {
       cout << "df";
    };
    cout << std::endl; 
    clock_t clk_end = clock();
    double used_time = (clk_start - clk_end) / CLOCKS_PER_SEC;
    std::cout << "Time cost: " << used_time << std::endl;
    return 0;
}
#elif defined TIME
int main(int argc, char **argv) {
    time_t times = time(NULL);
    std::cout << "Time: " << times << std::endl;
    char *time_str = ctime(&times);
    std::cout << time_str << std::endl;
    return 0;
}
#elif defined LOCALTIME
int main(int argc, char **argv) {
    time_t times = time(NULL);
    tm *tm_val = localtime(&times);
    std::cout << tm_val->tm_sec  << std::endl;
    return 0;
}
#elif defined ASCTIME

 
int main(int argc, char **argv) {
    time_t times = time(NULL);
    tm *tm_val = localtime(&times);
    char *time_string = asctime(tm_val);
    std::cout << time_string  << std::endl;
    return 0;
}
#elif defined MAKE_TIME
double get_second(char flag) 
{
    static struct timeval tv_start;
    static struct timeval tv_end;
    if (!flag) {
        gettimeofday(&tv_start, NULL); 
    } else if (flag == 1) {
        gettimeofday(&tv_end, NULL); 
        long times = (tv_end.tv_usec - tv_start.tv_usec) / 1000 +
        (tv_end.tv_sec - tv_end.tv_sec) * 1000; 
        return times;
    } 
        return 0;
}
 
int main(int argc, char **argv) {
    get_second(0);
    time_t times = time(NULL);
    tm *tm_val = localtime(&times);
    for (int i=1; i < 1000; ++i);
    time_t tvs = mktime(tm_val);
    std::cout << tvs << std::endl;
    double timesss = get_second(1);
    std::cout << timesss << std::endl;
    return 0;
}
#endif
