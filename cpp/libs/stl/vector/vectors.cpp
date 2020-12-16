/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-04 09:34
 * Last modified : 2020-08-04 09:34
 * Filename      : vector.cpp
 * Description   : 
*********************************************************************/

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
#define TEST3
#if defined TEST0

int main(int argc, char **argv)
{
    vector<double> value0;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
    std::cout << value0.max_size() << std::endl;
    
    value0.reserve(10); 
    std::cout << value0.max_size() << std::endl;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
   
    value0.resize(20);
    std::cout << value0[1] << std::endl;
    std::cout << value0.max_size() << std::endl;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;

    value0.reserve(30); 
    std::cout << value0.max_size() << std::endl;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
    std::cout << value0[1] << std::endl;
    return 0;
}
#elif defined TEST1
int main(int argc, char **argv)
{
    vector<double> value0(10, 8);
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
    for (auto i: value0) std::cout << i << std::endl;
    std::cout << value0[1] << std::endl;
    return 0;
}
#elif defined TEST2
int main(int argc, char **argv)
{
    vector<double> value0{1, 1.1, 1, 3, 4.5};
    vector<double> value1{11, 1, 5, 3, 2};
    value0.reserve(30); 
    value0.resize(20);
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    value0.assign(4, 3);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;

    value0.assign(value1.begin(), value1.end());
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    std::cout << value0.capacity() << std::endl;
    std::cout << value0.size() << std::endl;
    value0.push_back(1);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    value0.pop_back();
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    value0.insert(value0.begin(), 4);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    std::cout << "=======================" << std::endl;
    value0.insert(value0.begin(), 4, 3);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;

    std::cout << "test2-----------------" << std::endl;
    value0.insert(value0.begin(),value1.begin(), value1.end());
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;

    std::cout << "test3-----------------" << std::endl;
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    value0.erase(std::begin(value0));
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    // value0.erase(std::begin(value0), std::end(value0));
    // value0.clear();
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    value0.swap(value1);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    for (auto i: value1) std::cout << i;
    std::cout << std::endl;
    return 0;
}
#elif defined TEST3
int main(int argc, char **argv)
{
    vector<double> value0{1,1,1,1,1,1,1,1};
    vector<double> value1{2,2,2,2,2,2,2,2};
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    for (auto i: value1) std::cout << i;
    std::cout << std::endl;
    value0.swap(value1);
    for (auto i: value0) std::cout << i;
    std::cout << std::endl;
    for (auto i: value1) std::cout << i;
    std::cout << std::endl;
    return 0;
}
#endif
