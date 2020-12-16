/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-05 17:58
 * Last modified : 2020-08-05 17:58
 * Filename      : next+prev.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <list>

using namespace std;
#define test1
#if defined test0
int main(int argc, char **argv) {
    std::list<int> mylist{1, 2, 4, 5, 7};
    // std::list<int>::iterator iter = std::next(mylist.begin(), 2);
    // std::cout << *iter << std::endl;
    std::list<int>::iterator iter = std::next(mylist.begin(), -2);
    std::cout << *iter << std::endl;
    return 0;
}
#elif defined test1
int main(int argc, char **argv)
{
    std::list<int> mylist{1,2,3,4,5,6,7,8};
    std::list<int>::iterator iter = std::prev(mylist.end(), 6);
    std::cout << *iter << std::endl;
    return 0;
}
#endif
