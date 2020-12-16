/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-02 10:55
 * Last modified : 2020-08-02 10:55
 * Filename      : monkey_eat_peach.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;
namespace tools {
    int sum_of_peach(int n) {
        int p_next = 1, p_prev;
        for (int i=0; i<n-1; ++i) {
            p_prev = (p_next + 1) * 2;
            p_next = p_prev;
        }   
        return p_prev;
    } 
}
int main(int argc, char **argv)
{
    int total_peach = tools::sum_of_peach(10);
    cout << total_peach << endl;
    return 0;
}
