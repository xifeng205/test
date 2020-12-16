/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 13:03
 * Last modified : 2020-07-17 13:03
 * Filename      : trailing_return_type.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <typeinfo>

using namespace std;

namespace tools {
    template <typename T1, typename T2>
        auto add(T1 a, T2 b) -> decltype(a+b) { return a + b; }
}

int main(int argc, char **argv)
{
    auto val = tools::add(4, 6);
    std::cout << val << std::endl;
    return 0;
}
