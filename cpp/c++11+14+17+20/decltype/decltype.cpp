/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-17 10:02
 * Last modified : 2020-07-17 10:02
 * Filename      : decltype.cpp
 * Description   : 
*********************************************************************/
//  decltype 推导规则
// 上面的例子让我们初步感受了一下 decltype 的用法，但你不要认为 decltype 就这么简单，它的玩法实际上可以非常复杂。当程序员使用 decltype(exp) 获取类型时，编译器将根据以下三条规则得出结果：
//
//     如果 exp 是一个不被括号( )包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，那么 decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况。
//     如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致。
//     如果 exp 是一个左值，或者被括号( )包围，那么 decltype(exp) 的类型就是 exp 的引用；假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
class decltype_test {
    public:
        int a;
        const int b;
        static int c;
};

int decltype_test::c = 1;

int func_int(double d) {return 0;}
int main(int argc, char **argv)
{
    int a = 1;
    decltype(a) e = a;
    const std::type_info &t_info_i = typeid(e);
    std::cout << t_info_i.name() << std::endl;

    const int b = 2;
    decltype(b) f = b;
    std::string str = "hellow world.";
    decltype(str) g = str;;
    const std::type_info &t_info_s = typeid(str);
    std::cout << t_info_s.name() << std::endl;

    decltype(func_int) ee;
    const std::type_info &tp_info_func = typeid(ee);
    std::cout << tp_info_func.name() << std::endl;
    
    decltype(1+3) ii;
    const std::type_info &tp_info_ii = typeid(ii);
    std::cout << tp_info_ii.name() << std::endl;
    
    int n = 0;
    int m = 1;
    decltype(n = n + m) ddd = m;
    const std::type_info &tp_info_ddd = typeid(ddd);
    std::cout << tp_info_ddd.name() << std::endl;

    // decltype((2+4)) kkk;
    // const std::type_info &tp_info_kkk = typeid(kkk);
    // std::cout << tp_info_kkk.name() << std::endl;

    decltype((n)) kkk=n;
    const std::type_info &tp_info_kkk = typeid(kkk);
    std::cout << tp_info_kkk.name() << std::endl;

    return 0;
}
