
/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 11:01
 * Last modified : 2020-07-10 11:01
 * Filename      : sort.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

//sort 注意事项
//1 容器支持的迭代器必须为随即访问迭代器；
//2 如果对容器中指定区域的元素做默认升序排序，则元素类型必须支持<小于运算符；同样，如果选用标准库提供的其它排序规则，元素类型也必须支持该规则底层实现所用的比较运算符；
//3 sort() 函数在实现排序时，需要交换容器中元素的存储位置。这种情况下，如果容器中存储的是自定义的类对象，则该类的内部必须提供移动构造函数和移动赋值运算符 
using namespace std;
bool fuc_sort(int i, int j) {
    return (i < j);
}
class fuc_sort_obj {
    public:
        bool operator()(int i, int j) {
            return i > j;
        }
};
int main(int argc, char **argv)
{
    std::vector<int> myvector{2, 3, 4, 1, 8, 7, 5, 6, 88};

    std::partial_sort(myvector.begin(), myvector.begin()+3, myvector.end(), fuc_sort_obj());
    for (std::vector<int>::iterator it = myvector.begin();
            it != myvector.end(); ++it)
        std::cout  << *it;

    std::cout << endl;

    return 0; 
}


