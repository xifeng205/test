/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 11:48
 * Last modified : 2020-07-10 11:48
 * Filename      : stable_sort.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    std::vector<int> myvector{1, 2, 5, 3, 5, 8, 3, 9};
    std::stable_sort(myvector.begin(), myvector.end());

    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << *it;
    std::cout << endl;

    return 0;
}
