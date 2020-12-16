/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 13:41
 * Last modified : 2020-07-17 13:41
 * Filename      : func_template.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

namespace tools {
    // template<typename R = int, typename T>
        // R add(T u, T v) { return u + v;}
}
template <typename T>
struct identity
{
    typedef T type;
};
template <typename T = int>
void func(typename identity<T>::type val, T a = 0)
{
    cout << val << endl;
    cout << a << endl;
}
int main(void)
{
    func(123.111);         // T -> int
    func(123.11, 123.111);  // T -> double
    return 0;
}
