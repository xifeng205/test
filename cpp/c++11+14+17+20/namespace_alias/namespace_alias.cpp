/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 13:16
 * Last modified : 2020-07-17 13:16
 * Filename      : namespace_alias.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

namespace math_tools {
    template <typename T>
        using p_func = T (*)(T, T);

    template <typename T1, typename T2>
       auto _add(T1 a, T2 b) -> decltype(a+b) { return a+b; }
}

int main(int argc, char **argv)
{
    math_tools::p_func<int> add =math_tools:: _add;
    auto c = add(3, 5);
    std::cout << c << std::endl;
    return 0;
}
