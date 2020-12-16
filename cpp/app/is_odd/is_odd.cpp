/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-01 13:59
 * Last modified : 2020-08-01 13:59
 * Filename      : is_odd.cpp
 * Description   : 
*********************************************************************/

#include <ios>
#include <iostream>

using namespace std;
namespace tools_n {
   bool is_odd(int integer) {
        return (integer % 2 == 1);
   } 
}
int main(int argc, char **argv)
{
    cout << tools_n::is_odd(4) << std::endl;
    cout << tools_n::is_odd(1) << std::endl;
    cout << "only a test" << std::endl;
    return 0;
}
