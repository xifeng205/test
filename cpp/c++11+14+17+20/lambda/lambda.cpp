/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-12 16:23
 * Last modified : 2020-05-12 16:23
 * Filename      : lambda.cpp
 * Description   : 
*********************************************************************/
//
// #include <iostream>
//
// using namespace std;
//
// int main(int argc, char* argv[])
// {
//     int a = 5, b = 7;
//     auto total = [](int x, int y)->int {return x + y; };    //接受两个参数
//     cout << total(a, b)<<endl;  //12
//     auto fun1 = [=] {return a + b; };   //值传递捕捉父作用域变量
//     cout << fun1() << endl; //12
//     auto fun2 = [&](int c) {b = a + c; a = 1; };    //省略了返回值类型，引用捕获所有
//     fun2(3);    //1 8
//     cout << a <<" "<< b << endl;
//     a = 5; b = 7;   //被修改后，重新赋值
//     auto fun3 = [=, &b](int c) mutable {b = a + c; a = 1; };    //以值传递捕捉的变量，在函数体里如果要修改，要加mutaple,因为默认const修饰
//     fun3(3);
//     cout << a << " " <<b<< endl;    //5,8
//     a = 5; b = 7;   //被修改后，重新赋值
//     auto fun4 = [=](int x, int y) mutable->int {a += x; b += y; return a + b; };
//     int t = fun4(10, 20);
//     cout << t << endl;  //42
//     cout << a <<" "<< b << endl;    //5 7
//     return 0;
// }
//
//
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
//     C++11新增了lambda函数，其基本格式如下
//
// 1 [捕捉列表] (参数) mutable -> 返回值类型 {函数体}
//
// 说明
//
//     []是lambda的引出符，捕捉列表能够捕捉上下文中的变量，来供lambda函数使用：
//
// 　　　　[var] 表示以值传递方式捕捉变量var
// 　　　　[=] 表示值传递捕捉所有父作用域变量
// 　　　　[&var] 表示以引用传递方式捕捉变量var
// 　　　　[&] 表示引用传递捕捉所有父作用域变量
// 　　　　[this] 表示值传递方式捕捉当前的this指针
//     　　　还有一些组合：
// 　　　　[=,&a] 表示以引用传递方式捕捉a,值传递方式捕捉其他变量
//     　　　注意：
//     　　　捕捉列表不允许变量重复传递，如：[=,a]、[&,&this]，会引起编译时期的错误
//
//     参数列表与普通函数的参数列表一致。如果不需要传递参数，可以联连同()一同【省略】。
//
//     mutable 可以取消Lambda的常量属性，因为Lambda默认是const属性；multable仅仅是让Lamdba函数体修改值传递的变量，但是修改后并不会影响外部的变量。
//
//     ->返回类型如果是void时，可以连->一起【省略】，如果返回类型很明确，可以省略，让编译器自动推倒类型。
//
//     函数体和普通函数一样，除了可以使用参数之外，还可以使用捕获的变量。
//
// 最简单的Lambda函数：
    int a = 5, b = 7;
    auto total = [](int x,int y)->int {return x + y;}; 
    cout << total(a, b) <<endl;
    auto fun = [=] {return a + b;};
    cout << fun() << endl;
    auto fun2 = [&](int c) {b = c + a; a = 1;};
    cout << a << b << endl;
    fun2(3);
    cout << a << b << endl;
    a = 5; b = 7;
    cout << a << b << endl;
    auto fun3 = [=, &b](int c) mutable {b = a + c; a = 1;};
    fun3(3);
    cout << a << b << endl;
    a = 5; b = 7;
    auto fun4 = [=](int x, int y) mutable -> int {
        a += 1;
        b += 2;
        return a + b;
    };
    int t = fun4(2, 4);
    cout << t <<endl;
    cout << a << b << endl;


}









