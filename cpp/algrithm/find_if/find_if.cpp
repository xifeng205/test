/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 15:12
 * Last modified : 2020-07-10 15:12
 * Filename      : find_if.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool mycomp0(int val){
    return (val%2);
}
int main(int argc, char **argv)
{
    std::vector<int> myvector{1, 3, 4, 6, 7, 9};
    std::vector<int>::iterator it = 
        find_if(myvector.begin(), myvector.end(), mycomp0);
    std::cout << *it << std::endl;

    int array[]{1, 3, 4, 5, 6, 8};
    int *find_if_p = find_if(array, array+7, mycomp0);
    std::cout << *find_if_p << std::endl;
    return 0;
}
