/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-30 10:04
 * Last modified : 2020-07-30 10:04
 * Filename      : static.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

#define LOCAL_VAR
#if defined LOCAL_VAR
namespace func_n {
    static int a = 1;
    void func_static() {
        static int a = 1;
        std::cout << a << std::endl; 
        ++a;
    }
    void func_static_call() {
        std::cout << a << std::endl; 
    }
};
int main(int argc, char **argv)
{
    func_n::func_static();
    func_n::func_static_call();
    func_n::func_static();
    return 0;
}
#endif
