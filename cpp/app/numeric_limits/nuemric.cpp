/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-30 09:32
 * Last modified : 2020-07-30 09:32
 * Filename      : nuemric.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <limits>
using namespace std;

int main(int argc, char **argv)
{
    cout << numeric_limits<int>::max() << std::endl; 
    cout << numeric_limits<int>::min() << std::endl; 
    cout << numeric_limits<bool>::min() << std::endl; 
    cout << numeric_limits<bool>::max() << std::endl; 
    return 0;
}
