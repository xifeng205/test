/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 12:49
 * Last modified : 2020-07-10 12:49
 * Filename      : partial_sort_copy.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int main(int argc, char **argv)
{
    int pc_array[5]{0};
    std::vector<int> myvector{1, 2, 3, 3, 6, 4, 9, 4, 6, 7, 8};
    std::partial_sort_copy(myvector.begin(), myvector.end(), pc_array, pc_array+5);
    for ( std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it )
        std::cout << *it;
    std::cout << endl;
    
    for (auto i : pc_array)
        std::cout << i;
    std::cout << endl;
    return 0;
}
