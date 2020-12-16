/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-14 14:59
 * Last modified : 2020-07-14 14:59
 * Filename      : copy.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char **argv)
{
    int arr[]{1, 4, 4, 5};
    std::copy(arr, arr+4, std::ostream_iterator<int>{std::cout, " "});
    return 0;
}
