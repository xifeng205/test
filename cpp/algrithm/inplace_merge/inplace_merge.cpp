/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 14:21
 * Last modified : 2020-07-10 14:21
 * Filename      : inplace_merge.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int myarray[]{1, 5, 4, 8, 2, 6, 9, 3, 7, 0};
    std::inplace_merge(myarray, myarray+5, myarray+11);
    for (auto i: myarray)
        cout << i;
    cout << endl;

    return 0;
}
