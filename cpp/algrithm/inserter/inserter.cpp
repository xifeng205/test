/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-14 15:39
 * Last modified : 2020-07-14 15:39
 * Filename      : inserter.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    std::vector<int> myvector{1, 3, 4, 5, 7};
    auto it = std::inserter(myvector, myvector.begin());
    return 0;
}
