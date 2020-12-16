/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 15:49
 * Last modified : 2020-07-10 15:49
 * Filename      : find_end.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool mycomp(int val1, int val2) {
    return (val2 == val2);
}
int main(int argc, char **argv)
{
    std::vector<int> myvector{1, 2, 3,4, 3, 4, 5, 1, 3, 1, 2, 3, 1, 2, 3};
    int arr[]{1, 2, 3};
    std::vector<int>::iterator it = 
        find_end(myvector.begin(), myvector.end(), arr, arr+3);
    cout << *it << endl;
    cout << it-myvector.begin() << endl;
    return 0;
}
