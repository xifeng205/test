/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-11 13:03
 * Last modified : 2020-07-11 13:03
 * Filename      : partition_copy.cpp
 * Description   : 
*********************************************************************/
// C++ partition()和stable_partition()函数》一节中，已经详细介绍了 partition() 和 stable_partition() 函数的功能和用法。不知道读者是否发现，这 2 个函数在实现功能时，都直接修改了原序列中元素的存储位置。
//
// 而在某些场景中，我们需要类似 partition() 或者 stable_partition() 函数“分组”的功能，但并不想对原序列做任何修改。这种情况下，就可以考虑使用 partition_copy() 函数。
//
// 和 stable_partition() 一样，partition_copy() 函数也能按照某个筛选规则对指定区域内的数据进行“分组”，并且分组后不会改变各个元素的相对位置。更重要的是，partition_copy() 函数不会对原序列做修改，而是以复制的方式将序列中各个元组“分组”到其它的指定位置存储。
//
// 举个例子，有如下一个数组 a[10]：
//
// 1 2 3 4 5 6 7 8 9
// 假设筛选条件为 i%2==0（也就是筛选出偶数），如果借助 stable_partition() 函数，则数组 a[10] 中元素的存储顺序会变成：
//
// 2 4 6 8 1 3 5 7 9
// 而如果选用同样的筛选规则，使用 partition_copy() 函数还需要为其配备 2 个存储空间（例如 b[10] 和 c[10]），其中 b[10] 用于存储符合筛选条件的偶数，而 c[10] 用于存储不符合筛选条件的奇数，也就是说，partition_copy() 函数执行的最终结果为：
//
// a[10]: 1 2 3 4 5 6 7 8 9
// b[10]: 2 4 6 8
// c[10]: 1 3 5 7 9
//
//     注意，这里仅展示了 b[10] 和 c[10] 数组中存储的有效数据。
//
//
// 值得一提的是，partition_copy() 函数定义在<algorithm>头文件中，其语法格式如下：
//
// pair<OutputIterator1,OutputIterator2> partition_copy (
//                     InputIterator first, InputIterator last,
//                     OutputIterator1 result_true, OutputIterator2 result_false,
//                     UnaryPredicate pred);
//
// 其中，各个参数的含义为：
//
//     first、last：都为输入迭代器，其组合 [first, last) 用于指定该函数处理的数据区域；
//     result_true：为输出迭代器，其用于指定某个存储区域，以存储满足筛选条件的数据；
//     result_false：为输出迭代器，其用于指定某个存储区域，以存储满足筛选条件的数据；
//     pred：用于指定筛选规则，其本质就是接收一个具有 1 个参数且返回值类型为 bool 的函数。注意，该函数既可以是普通函数，还可以是一个函数对象。
//
//
// 除此之外，该函数还会返回一个 pair 类型值，其包含 2 个迭代器，第一个迭代器指向的是 result_true 区域内最后一个元素之后的位置；第二个迭代器指向的是 result_false 区域内最后一个元素之后的位置
// C++ 标准库中还给出了 partition_copy() 函数底层实现的参考代码，感兴趣的读者可自行研究，这里不再进行过多赘述。
 //
 // template <class InputIterator, class OutputIterator1,
 //           class OutputIterator2, class UnaryPredicate pred>
 //           pair<OutputIterator1,OutputIterator2>
 // partition_copy (InputIterator first, InputIterator last,
 //                 OutputIterator1 result_true, OutputIterator2 result_false,
 //                 UnaryPredicate pred)
 // {
 //     while (first!=last) {
 //         if (pred(*first)) {
 //             *result_true = *first;
 //             ++result_true;
 //         }
 //         else {
 //             *result_false = *first;
 //             ++result_false;
 //         }
 //         ++first;
 //     }
 //     return std::make_pair (result_true,result_false);
 // }
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool mycomp(int i) { return (i%2 == 0); }
    
int main(int argc, char **argv)
{
    std::vector<int> myvector{1,2,3,4,5,6,7,8,9};    
    int b[10]{0}, c[10]{0};
    pair<int*, int*> result = 
        partition_copy(myvector.begin(), myvector.end(), b, c, mycomp);
    std::cout << "b[10]:";
    for (int *p=b; p<result.first; ++p) std::cout << *p << "";
    std::cout << endl; 

    std::cout << "c[10]:";
    for (int *p=c; p<result.second; ++p) std::cout << *p << ""; 
    std::cout << endl; 
    return 0;
}
