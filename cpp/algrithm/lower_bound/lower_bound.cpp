/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-13 17:49
 * Last modified : 2020-07-13 17:49
 * Filename      : lower_bound.cpp
 * Description   : 
*********************************************************************/

// 前面章节中，已经给大家系统地介绍了几个查找函数，如 find()、find_if()、search() 等。值得一提的是，这些函数的底层实现都采用的是顺序查找（逐个遍历）的方式，在某些场景中的执行效率并不高。例如，当指定区域内的数据处于有序状态时，如果想查找某个目标元素，更推荐使用二分查找的方法（相比顺序查找，二分查找的执行效率更高）。
//
// 幸运的是，除了前面讲过的几个函数外，C++ STL标准库中还提供有 lower_bound()、upper_bound()、equal_range() 以及 binary_search() 这 4 个查找函数，它们的底层实现采用的都是二分查找的方式。
//
// 从本节开始，将给大家系统地讲解这 4 个二分查找函数的功能和用法，这里先从 lower_bound() 函数开始讲起。
//
//     有关二分查找算法的实现原理，感兴趣的读者可阅读《二分查找（折半查找）》一节做详细了解。
//
// C++ lower_bound()函数
// lower_bound() 函数用于在指定区域内查找不小于目标值的第一个元素。也就是说，使用该函数在指定范围内查找某个目标值时，最终查找到的不一定是和目标值相等的元素，还可能是比目标值大的元素。
//
// lower_bound() 函数定义在<algorithm>头文件中，其语法格式有 2 种，分别为：
//
// //在 [first, last) 区域内查找不小于 val 的元素
// ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
//                              const T& val);
// //在 [first, last) 区域内查找第一个不符合 comp 规则的元素
// ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last,
//                              const T& val, Compare comp);
//
// 其中，first 和 last 都为正向迭代器，[first, last) 用于指定函数的作用范围；val 用于指定目标元素；comp 用于自定义比较规则，此参数可以接收一个包含 2 个形参（第二个形参值始终为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。
//
//     实际上，第一种语法格式也设定有比较规则，只不过此规则无法改变，即使用 < 小于号比较 [first, last) 区域内某些元素和 val 的大小，直至找到一个不小于 val 的元素。这也意味着，如果使用第一种语法格式，则 [first,last) 范围的元素类型必须支持 < 运算符。
//
// 此外，该函数还会返回一个正向迭代器，当查找成功时，迭代器指向找到的元素；反之，如果查找失败，迭代器的指向和 last 迭代器相同。
//
// 再次强调，该函数仅适用于已排好序的序列。所谓“已排好序”，指的是 [first, last) 区域内所有令 element<val（或者 comp(element,val)，其中 element 为指定范围内的元素）成立的元素都位于不成立元素的前面。
//注意，myvector 容器中存储的元素看似是乱序的，但对于元素 3 来说，大于 3 的所有元素都位于其左侧，小于 3 的所有元素都位于其右侧，且查找规则选用的是 mycomp2()，其查找的就是第一个不大于 3 的元素，因此 lower_bound() 函数是可以成功运行的。
//
// C++ STL标准库给出了 lower_bound() 函数底层实现的参考代码（如下所示），感兴趣的读者可自行研究，这里不再赘述：
//
//     template <class ForwardIterator, class T>
//     ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val)
//     {
//         ForwardIterator it;
//         iterator_traits<ForwardIterator>::difference_type count, step;
//         count = distance(first,last);
//         while (count>0)
//         {
//             it = first; step=count/2; advance (it,step);
//             if (*it<val) {  //或者 if (comp(*it,val))，对应第 2 种语法格式
//                 first=++it;
//                 count-=step+1;
//             }
//             else count=step;
//         }
//         return first;
//     }


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

bool mycomp(int i, int j) { return (i<j); }

int main(int argc, char **argv)
{
    int a[]{1,2,4,6,7,5};
    int *p = lower_bound(a, a+6, 6, mycomp);
    cout << *p << endl; 
    return 0;
}
