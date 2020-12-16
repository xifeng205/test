/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-10 13:33
 * Last modified : 2020-07-10 13:33
 * Filename      : is_sorted.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

bool less_sort(int i, int j) {
    return i < j;
}
class greater_sort {
    public:
        bool operator()(int i, int j) {
            return i > j;
        }
};

int main(int argc, char **argv)
{
    std::array<int, 10> myvector0{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> myvector{1, 3, 5, 6, 3, 2, 4};
    if (std::is_sorted(myvector0.begin(), myvector0.end(), less_sort))
        std::cout << "Alreadly sorted!"<< endl;

    return 0;
}
