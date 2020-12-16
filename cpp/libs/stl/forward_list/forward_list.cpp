/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-04 16:39
 * Last modified : 2020-08-04 16:39
* Filename      : forward_list.cpp
* Description   : 
*********************************************************************/

#include <iostream>
#include <forward_list>

using namespace std;

int main(int argc, char **argv)
{
    forward_list<int> flist{1,2,8,5,1,1,1,1};
    std::cout << std::distance(flist.begin(), flist.end()) << std::endl;;
    auto iter = flist.begin();
    std::advance(iter, 3);
    std::cout << *iter << std::endl;

    return 0;
}
