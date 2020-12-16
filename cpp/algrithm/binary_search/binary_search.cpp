/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-13 21:11
 * Last modified : 2020-07-13 21:11
 * Filename      : binary_search.cpp
 * Description   : 
*********************************************************************/
// binary_search() 函数定义在<algorithm>头文件中，用于查找指定区域内是否包含某个目标元素。
//
// 该函数有 2 种语法格式，分别为：
//
// //查找 [first, last) 区域内是否包含 val
// bool binary_search (ForwardIterator first, ForwardIterator last,
//                       const T& val);
// //根据 comp 指定的规则，查找 [first, last) 区域内是否包含 val
// bool binary_search (ForwardIterator first, ForwardIterator last,
//                       const T& val, Compare comp);
//
// 其中，first 和 last 都为正向迭代器，[first, last) 用于指定该函数的作用范围；val 用于指定要查找的目标值；comp 用于自定义查找规则，此参数可接收一个包含 2 个形参（第一个形参值为 val）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。
//
// 同时，该函数会返回一个 bool 类型值，如果 binary_search() 函数在 [first, last) 区域内成功找到和 val 相等的元素，则返回 true；反之则返回 false。
//
// 需要注意的是，由于 binary_search() 底层实现采用的是二分查找的方式，因此该函数仅适用于“已排好序”的序列。所谓“已排好序”，并不是要求 [first, last) 区域内的数据严格按照某个排序规则进行升序或降序排序，只要满足“所有令 element<val（或者 comp(val, element）成立的元素都位于不成立元素的前面（其中 element 为指定范围内的元素）”即可。
//
   #include <iostream>     // std::cout
    #include <algorithm>    // std::binary_search
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
        int a[7] = { 1,2,3,4,5,6,7 };
        //从 a 数组中查找元素 4
        bool haselem = binary_search(a, a + 9, 4);
        cout << "haselem：" << haselem << endl;
        vector<int>myvector{ 4,5,3,1,2 };
        //从 myvector 容器查找元素 3
        bool haselem2 = binary_search(myvector.begin(), myvector.end(), 3, mycomp2());
        cout << "haselem2：" << haselem2;
        return 0;
    }
// 此程序中演示了 binary_search() 函数的 2 种适用场景，其中 a[7] 数组中存储的为升序序列；而 myvector 容器中存储的序列虽然整体是乱序的，但对于目标元素 3 来说，所有符合 mycomp2(element, 3) 规则的元素都位于其左侧，不符合的元素都位于其右侧，因此 binary_search() 函数仍可正常执行。
//
// C++ STL标准库给出了 binary_search() 函数底层实现的参考代码（如下所示），感兴趣的读者可自行研究，这里不再赘述：
//
//     //第一种语法格式的实现
//     template <class ForwardIterator, class T>
//     bool binary_search (ForwardIterator first, ForwardIterator last, const T& val)
//     {
//         first = std::lower_bound(first,last,val);
//         return (first!=last && !(val<*first));
//     }
//     //第二种语法格式的底层实现
//     template<class ForwardIt, class T, class Compare>
//     bool binary_search(ForwardIt first, ForwardIt last, const T& val, Compare comp)
//     {
//         first = std::lower_bound(first, last, val, comp);
//         return (!(first == last) && !(comp(val, *first)));
//     }
