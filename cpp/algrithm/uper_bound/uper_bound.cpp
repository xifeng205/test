/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-13 19:54
 * Last modified : 2020-07-13 19:54
 * Filename      : uper_bound.cpp
 * Description   : 
*********************************************************************/
// 《C++ lower_bound()》一节中，系统地介绍了 lower_bound() 二分法查找函数的功能和用法，在此基础上，本节再讲解一个功能类似的查找函数，即 upper_bound() 函数。
//
// upper_bound() 函数定义在<algorithm>头文件中，用于在指定范围内查找大于目标值的第一个元素。该函数的语法格式有 2 种，分别是：
//
// //查找[first, last)区域中第一个大于 val 的元素。
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,
//                              const T& val);
// //查找[first, last)区域中第一个不符合 comp 规则的元素
// ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,
//                              const T& val, Compare comp);
//
// 其中，first 和 last 都为正向迭代器，[first, last) 用于指定该函数的作用范围；val 用于执行目标值；comp 作用自定义查找规则，此参数可接收一个包含 2 个形参（第一个形参值始终为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。
//
//     实际上，第一种语法格式也设定有比较规则，即使用 < 小于号比较 [first, last) 区域内某些元素和 val 的大小，直至找到一个大于 val 的元素，只不过此规则无法改变。这也意味着，如果使用第一种语法格式，则 [first,last) 范围的元素类型必须支持 < 运算符。
//
// 同时，该函数会返回一个正向迭代器，当查找成功时，迭代器指向找到的元素；反之，如果查找失败，迭代器的指向和 last 迭代器相同。
//
// 另外，由于 upper_bound() 底层实现采用的是二分查找的方式，因此该函数仅适用于“已排好序”的序列。注意，这里所说的“已排好序”，并不要求数据完全按照某个排序规则进行升序或降序排序，而仅仅要求 [first, last) 区域内所有令 element<val（或者 comp(val, element）成立的元素都位于不成立元素的前面（其中 element 为指定范围内的元素）。
//
//     有关二分查找算法，读者可阅读《二分查找算法》一节。
//
#include <iostream>     // std::cout
#include <algorithm>    // std::upper_bound
#include <vector>       // std::vector
using namespace std;
//以普通函数的方式定义查找规则
bool mycomp(int i, int j) { return i > j; }
//以函数对象的形式定义查找规则
class mycomp2 {
public:
    bool operator()(const int& i, const int& j) {
        return i > j;
    }
};
int main() {
    int a[5] = { 1,2,3,4,5 };
    //从 a 数组中找到第一个大于 3 的元素
    int *p = upper_bound(a, a + 5, 3);
    cout << "*p = " << *p << endl;
    vector<int> myvector{ 4,5,3,1,2 };
    //根据 mycomp2 规则，从 myvector 容器中找到第一个违背 mycomp2 规则的元素
    vector<int>::iterator iter = upper_bound(myvector.begin(), myvector.end(), 3);
    cout << "*iter = " << *iter;
    return 0;
}
