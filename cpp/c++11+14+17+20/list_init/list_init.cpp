
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 10:02
 * Last modified : 2020-07-17 10:02
 * Filename      : decltype.cpp
 * Description   : 
*********************************************************************/
#include <iostream>
#include <string>

using namespace std;
namespace tools {
    struct  func_r {
        int a;
        double b;
    };
    template<typename T1, typename T2>
    func_r get_func(T1 a, T2 b) { return {a, b}; }
}

int main(int argc, char **argv)
{
    int a = 4; double b = 6.7;
    auto i = tools::get_func(a, b);   
    cout << i.a << " " <<  i.b<< endl;
    return 0;
}
