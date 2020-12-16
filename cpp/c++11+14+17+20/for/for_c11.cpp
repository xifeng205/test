/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-03 15:00
 * Last modified : 2020-07-03 15:00
 * Filename      : for_c11.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <array>

using namespace std;

int main(int argc, char **argv)
{
    array<int, 5> for_test = {1, 1, 3, 4, 5};
    for (auto i : for_test) cout << i << endl;
    return 0;
}
