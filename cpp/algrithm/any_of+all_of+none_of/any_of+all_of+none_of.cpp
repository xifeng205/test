/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-13 21:27
 * Last modified : 2020-07-13 21:27
 * Filename      : any_of+all_of+none_of.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    int arr[]{1,2,4,5,6,7,8,9}, a{10}, b{4};

    std::cout << "There are "
        << (std::none_of(arr, arr+8, [a](int age) {return a < age;})    
                ? "no" : "some") << " peoples" << endl;

    std::cout << "There are "
        << (std::any_of(arr, arr+8, [b](int age) {return b < age;}) 
                ? "some" : "no") << " peoples" << endl;

    int good_age{100};
    std::cout << "Threr are "  
        << (std::all_of(arr, arr+8, [good_age](int age) {return age < good_age;})
                ? " some" : "no" ) << " people" << endl;
    return 0;
}
