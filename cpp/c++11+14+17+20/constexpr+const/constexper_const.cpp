/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-07 15:10
 * Last modified : 2020-08-07 15:10
 * Filename      : constexper_const.cpp
 * Description   : 
 *********************************************************************/

#include <iostream>
#include <array>

using namespace std;
namespace test_n{
    // void make_array(const int x) {
        // std::array<int, x> arr; 
    // }
      
    void make_array (){
        constexpr int x = 10;         
        std::array<int, x> arr; 
    }

    const int add(int x, int y) {
        return x+y;
    }
    constexpr int add1(int x, int y) {
        return x+y;
    }
}

#define TEST1 
#if defned TEST1
int main(int argc, char **argv) {
    const int n = 10;
    int arr[n] = {1};
    cout << arr[0] << endl;
    return 0;
}
#elif defined TEST1
int main(int argc, char **argv)
{
    std::array<int, test_n::add1(1,3)> arr; 
    // std::array<int, add2(1,3)> arr; 
    return 0;
}
#elif defined TEST3

int main(int argc, char **argv)
{
    int main(int arc)
    return 0;
}
#endif
