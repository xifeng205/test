/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-16 21:26
 * Last modified : 2020-07-16 21:26
 * Filename      : auto.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int x = 1;
    auto &a = x;
    auto v = a; 
    cout << v << endl;
    cout << typeof(v)  <<  endl;
    return 0;
}
