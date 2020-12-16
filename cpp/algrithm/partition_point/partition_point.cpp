/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-12 13:04
 * Last modified : 2020-07-12 13:04
 * Filename      : partition_point.cpp
 * Description   : 
*********************************************************************/
// 在前面章节中，我们系统学习了 partition()、stable_partition() 和 partition_copy() 这 3 个函数，它们的功能本质上都是根据某个筛选规则对指定范围内的数据进行分组（即符合条件的为一组，不符合条件的为另一组），并且反馈给我们两组数据之间的分界位置。
//
// 事实上，有些数据本身就已经是按照某个筛选规则分好组的，例如：
//
// 1,2,3,4,5,6,7      <-- 根据规则 i<4，{1,2,3} 为一组，{4,5,6,7} 为另一组
// 2,4,6,8,1,3,5,7,9  <-- 根据规则 i%2=0，{2,4,6,8} 为一组，{1,3,5,7,9} 为另一组
//
// 类似上面这样已经“分好组”的数据，在使用时会有一个问题，即不知道两组数据之间的分界在什么位置。有读者可能想到，再调用一次 partition()、stale_partition() 或者 partition_copy() 不就可以了吗？这种方法确实可行，但对已经分好组的数据再进行一次分组，是没有任何必要的。
//
// 实际上，对于如何在已分好组的数据中找到分界位置，C++ 11标准库提供了专门解决此问题的函数，即 partition_point() 函数。
//
// partition_point() 函数定义在<algorithm>头文件中，其语法格式为：
//
// ForwardIterator partition_point (ForwardIterator first, ForwardIterator last,
//                                  UnaryPredicate pred);
//
// 其中，first 和 last 为正向迭代器，[first, last) 用于指定该函数的作用范围；pred 用于指定数据的筛选规则。
//
//     所谓筛选规则，其实就是包含 1 个参数且返回值类型为 bool 的函数，此函数可以是一个普通函数，也可以是一个函数对象。
//
// 同时，该函数会返回一个正向迭代器，该迭代器指向的是 [first, last] 范围内第一个不符合 pred 筛选规则的元素。
// 值得一提的是，C++ 11标准库中给出了 partition_point() 函数底层实现的参考代码（如下所示），感兴趣的读者可自行分析，这里不再进行赘述：
//
//     template <class ForwardIterator, class UnaryPredicate>
//     ForwardIterator partition_point (ForwardIterator first, ForwardIterator last,
//                                        UnaryPredicate pred)
//     {
//         auto n = distance(first,last);
//         while (n>0)
//         {
//             ForwardIterator it = first;
//             auto step = n/2;
//             std::advance (it,step);
//             if (pred(*it)) { first=++it; n-=step+1; }
//             else n=step;
//         }
//         return first;
//     }
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool mycomp(const int &i) {
    return (i%2==0); 
}
int main(int argc, char **argv)
{
    std::vector<int> myvector{2,4,6,8,1,3,5,7};
    std::vector<int>::iterator iter = 
        partition_point(myvector.begin(), myvector.end(), mycomp);
    
    std::cout << "First data: ";
    for (auto it=myvector.begin(); it != iter; ++it) std::cout << *it;
    std::cout << std::endl;

    std::cout << "Second data: ";
    for (auto it=iter; it != myvector.end(); ++it) std::cout << *it;
    std::cout << std::endl;
    return 0;
}





























