/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 16:52
 * Last modified : 2020-07-10 16:52
 * Filename      : partition.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

// partition 可直译为“分组”，partition() 函数可根据用户自定义的筛选规则，重新排列指定区域内存储的数据，使其分为 2 组，第一组为符合筛选条件的数据，另一组为不符合筛选条件的数据。
//
// 举个例子，假设有一个数组 a[9]，其存储数据如下：
//
// 1 2 3 4 5 6 7 8 9
// 在此基础上，如果设定筛选规则为 i%2=0（其中 i 即代指数组 a 中的各个元素），则借助 partition() 函数，a[9] 数组中存储数据的顺序可能变为：
//
// 1 9 3 7 5 6 4 8 2
// 其中 {1,9,3,7,5} 为第一组，{6,4,8,2} 为第二组。显然前者中的各个元素都符合筛选条件，而后者则都不符合。由此还可看出，partition() 函数只会根据筛选条件将数据进行分组，并不关心分组后各个元素具体的存储位置。
//
//     如果想在分组之后仍不改变各元素之间的相对位置，可以选用 stable_partition() 函数。有关此函数的功能和用法，本节后续会做详细讲解。
//
// 值得一提得是，partition() 函数定义于<algorithm>头文件中，因此在使用该函数之前，程序中应先引入此头文件：
//
//     #include <algorithm>
//
// 如下为 partition() 函数的语法格式：
//
// ForwardIterator partition (ForwardIterator first,
//                            ForwardIterator last,
//                            UnaryPredicate pred);
//
// 其中，first 和 last 都为正向迭代器，其组合 [first, last) 用于指定该函数的作用范围；pred 用于指定筛选规则。
//
//     所谓筛选规则，其本质就是一个可接收 1 个参数且返回值类型为 bool 的函数，可以是普通函数，也可以是一个函数对象。
//
// 同时，partition() 函数还会返回一个正向迭代器，其指向的是两部分数据的分界位置，更确切地说，指向的是第二组数据中的第 1 个元素。
#include <algorithm>
#include <vector>
bool mycomp(int i) {
    return (i%2 == 0);
}
int main(int argc, char **argv)
{
    std::vector<int> myvector{1,3,4,5,8,9,3,4,5,9};
    std::vector<int>::iterator it = 
        std::partition(myvector.begin(), myvector.end(), mycomp);
    std::cout << *it << std::endl;
    std::cout << it - myvector.begin() << endl;
    return 0;
}
