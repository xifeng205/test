/********************************************************************* * Author        : cuiyunpeng * Email         : @163.com
 * Create time   : 2020-07-30 16:42
 * Last modified : 2020-07-30 16:42
 * Filename      : inference.cpp
 * Description   : 
*********************************************************************/

#include <cstdio>
#include <iostream>

using namespace std;
namespace reference_n {
    int arr_val[10] {1, 2, 4, 5,6,8};
    int &set_val(int index) {
        return arr_val[index];
    }
}

int main(int argc, char **argv)
{
    reference_n::set_val(1) = 10;
    std::cout << reference_n::arr_val[1] << std::endl;
    return 0;
}
