/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 17:13
 * Last modified : 2020-07-10 17:13
 * Filename      : stable_partition.cpp
 * Description   : 
*********************************************************************/
//  C++ stable_partition()函数
// 前面提到，partition() 函数只负责对指定区域内的数据进行分组，并不保证各组中元素的相对位置不发生改变。而如果想在分组的同时保证不改变各组中元素的相对位置，可以使用 stable_partition() 函数。
//
// 也就是说，stable_partition() 函数可以保证对指定区域内数据完成分组的同时，不改变各组内元素的相对位置。
//
// 仍以数组 a[9] 举例，其存储的数据如下：
//
// 1 2 3 4 5 6 7 8 9
// 假定筛选规则为 i%2=0（其中 i 即代指数组 a 中的各个元素），则借助 stable_partition() 函数，a[9] 数组中存储数据的顺序为：
//
// 2 4 6 8 1 3 5 7 9
// 其中 {2,4,6,8} 为一组，{1,3,5,7,9} 为另一组。通过和先前的 a[9] 对比不难看出，各个组中元素的相对位置没有发生改变。
//
//     所谓元素的相对位置不发生改变，以 {2,4,6,8} 中的元素 4 为例，在原 a[9] 数组中，该元素位于 2 的右侧，6 和 8 的左侧；在经过 stable_partition() 函数处理后的 a[9] 数组中，元素 4 仍位于 2 的右侧，6 和 8 的左侧。因此，该元素的相对位置确实没有发生改变。
//
// stable_partition() 函数定义在<algorithm>头文件中，其语法格式如下：
//
// BidirectionalIterator stable_partition (BidirectionalIterator first,
//                                         BidirectionalIterator last,
//                                         UnaryPredicate pred);
//
// 其中，first 和 last 都为双向迭代器，其组合 [first, last) 用于指定该函数的作用范围；pred 用于指定筛选规则。
//
// 同时，stable_partition() 函数还会返回一个双向迭代器，其指向的是两部分数据的分界位置，更确切地说，指向的是第二组数据中的第 1 个元素。

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool mycomp(int i) {
    return (i%2==0);
}
int main(int argc, char **argv)
{
    std::vector<int> myvector{2,3,4,5,6,6,7,7,9,8};
    std::vector<int>::iterator it =
        std::stable_partition(myvector.begin(), myvector.end(), mycomp);
    cout << *it << endl;
    cout << it - myvector.begin() << endl;
    return 0;
}
