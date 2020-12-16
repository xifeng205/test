/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-04 14:34
 * Last modified : 2020-08-04 14:34
 * Filename      : lists.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <list>

using namespace std;
#define TEST2
#if defined TEST0
int main(int argc, char **argv)
{
    list<int> lst{1, 1, 1, 8, 1, 1, 1, 3} i ijdf ifids fdsf;
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;
    lst.reverse();

    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;

    lst.sort();
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;

    lst.sort([](int i, int j) { return i > j; });
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;

    lst.sort([](int i, int j) { return i < j; });
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;
    return 0;
}
#elif defined TEST1
int main(int argc, char **argv)
{
    list<int> lst{1, 1, 1, 1, 1, 1, 1, 1};
    list<int> lst1{2, 2, 2, 2, 2, 2, 2, 2};

    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;
    for (auto i : lst1)
        std::cout << i;
    std::cout << std::endl;

    lst.splice(lst.begin(), lst1);
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;
    for (auto i : lst1)
        std::cout << i;
    std::cout << std::endl;

    lst.splice(lst.begin(), lst1, std::begin(lst1), std::end(lst1));
    for (auto i : lst)
      std::cout << i;
    std::cout << std::endl;
    for (auto i : lst1)
        std::cout << i;
    std::cout << std::endl;

    return 0;
}
#elif defined TEST2
bool comp(int i, int j) {
    return (i == j);
}
int main(int argc, char **argv)
{
    list<int> lst{1, 1, 1, 1, 1, 1, 1, 1};
    list<int> lst1{2, 2, 2, 2, 2, 2, 2, 2};

    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;
    for (auto i : lst1)
        std::cout << i;
    std::cout << std::endl;
    lst.unique(comp);
    for (auto i : lst)
        std::cout << i;
    std::cout << std::endl;




    return 0;
}
#endif
