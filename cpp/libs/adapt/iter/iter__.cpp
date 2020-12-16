/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-05 10:08
 * Last modified : 2020-08-05 10:08
 * Filename      : iter__.cpp
 * Description   :
 *********************************************************************/

#include <iostream>
#include <iterator>
#include <vector>
#include <list>

using namespace std;
#define TEST3
#if defined TEST0
int main(int argc, char **argv) {
    std::vector<int> __vector{1, 2, 4, 5, 4, 5};
    std::reverse_iterator<std::vector<int>::iterator> reservers_it_sta(
            __vector.begin());
    std::reverse_iterator<std::vector<int>::iterator> reservers_it_end(
            __vector.end());

    for (auto i = reservers_it_sta.base(); i != reservers_it_end.base(); ++i) {
        std::cout << *i << std::endl;
    }
}
#elif defined TEST1
int main(int argc, char **argv) {
    std::vector<int> myvector(2, 5);
    std::insert_iterator<std::vector<int>> inserter_it(myvector,
                                                       myvector.begin());
    inserter_it = 3;
    inserter_it = 4;
    inserter_it = 5;
    inserter_it = 6;
    inserter_it = 7;
    for (auto i = myvector.begin(); i != myvector.end(); ++i)
        std::cout << *i << std::endl;
    return 0;
}
#elif defined TEST2
int main(int argc, char **argv) {
    std::vector<int> myvector(2, 5);
    std::back_insert_iterator<std::vector<int>> inserter_it(myvector);
    inserter_it = 3;
    inserter_it = 4;
    inserter_it = 5;
    inserter_it = 6;
    inserter_it = 7;
    for (auto i = myvector.begin(); i != myvector.end(); ++i)
        std::cout << *i << std::endl;
    return 0;
}
#elif defined TEST3
int main(int argc, char **argv) {
    std::list<int> mylist(3,5);
    std::front_insert_iterator<std::list<int>> front_iter(mylist);
    front_iter = 1;
    front_iter = 1;
    front_iter = 1;
    front_iter = 1;
    for (auto it = mylist.begin(); it !=mylist.end(); ++it)
        std::cout << *it << std::endl;
    return 0;
}
#endif

