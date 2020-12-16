/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-17 12:14
 * Last modified : 2020-05-17 12:14
 * Filename      : signal.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;
void signal_handler(int signal_num) {
    cout << "Singal example."<< endl;
    exit(signal_num);
}
int main(int argc, char **argv)
{
    int i = 0;
    signal(SIGINT, signal_handler);
    while (1) {
        sleep(1);
       if (++i == 4) {
            raise(SIGINT);
       } 
    }
    return 0;
}
