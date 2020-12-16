/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 23:48
 * Last modified : 2020-07-17 23:48
 * Filename      : longlong.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <climits>

using namespace std;

int main(int argc, char **argv)
{
    cout << LLONG_MAX << " |" << hex << LLONG_MAX << endl;
    cout << LLONG_MIN << " |" << hex << LLONG_MIN << endl;
    cout << ULLONG_MAX<< " |" << hex << ULLONG_MAX << endl;
    return 0;
}
