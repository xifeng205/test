/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-13 20:17
 * Last modified : 2020-07-13 20:17
 * Filename      : equel_range.cpp
 * Description   : 
*********************************************************************/


// equel_range() 函数定义在<algorithm>头文件中，用于在指定范围内查找等于目标值的所有元素。
//
// 值得一提的是，当指定范围内的数据支持用 < 小于运算符直接做比较时，可以使用如下格式的 equel_range() 函数：
//
// //找到 [first, last) 范围中所有等于 val 的元素
// pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);
//
// 如果指定范围内的数据为自定义的类型（用结构体或类），就需要自定义比较规则，这种情况下可以使用如下格式的 equel_range() 函数：
//
// //找到 [first, last) 范围内所有等于 val 的元素
// pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
//
// 以上 2 种格式中，first 和 last 都为正向迭代器，[first, last) 用于指定该函数的作用范围；val 用于指定目标值；comp 用于指定比较规则，此参数可接收一个包含 2 个形参（第二个形参值始终为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。
//
// 同时，该函数会返回一个 pair 类型值，其包含 2 个正向迭代器。当查找成功时：
//
//     第 1 个迭代器指向的是 [first, last) 区域中第一个等于 val 的元素；
//     第 2 个迭代器指向的是 [first, last) 区域中第一个大于 val 的元素。
//
// 反之如果查找失败，则这 2 个迭代器要么都指向大于 val 的第一个元素（如果有），要么都和 last 迭代器指向相同。
//
// 需要注意的是，由于 equel_range() 底层实现采用的是二分查找的方式，因此该函数仅适用于“已排好序”的序列。所谓“已排好序”，并不是要求 [first, last) 区域内的数据严格按照某个排序规则进行升序或降序排序，只要满足“所有令 element<val（或者 comp(element,val）成立的元素都位于不成立元素的前面（其中 element 为指定范围内的元素）”即可。
//
//     有关二分查找算法，读者可阅读《二分查找算法》一节。
//
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

bool mycomp2(int i, int j) { return (i<j); }

using namespace std;

int main(int argc, char **argv)
{
    int a[]{1,2,3,4,4,4,4,8,9};
    std::pair<int *, int *> range =	equal_range(a, a+9, 4);
	for (auto i=range.first; i!=range.second; ++i)  
		cout << *i;
	cout << endl;

    vector<int>myvector{ 7,8,5,4,3,3,3,3,2,1 };
    pair<vector<int>::iterator, vector<int>::iterator> range2;
    //在 myvector 容器中找到所有的元素 3
    range2 = equal_range(myvector.begin(), myvector.end(), 3,mycomp2);
    cout << "\nmyvector：";
    for (auto it = range2.first; it != range2.second; ++it) {
        cout << *it << " ";
    }
    return 0;
}
