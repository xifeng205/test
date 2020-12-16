/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-30 14:49
 * Last modified : 2020-07-30 14:49
 * Filename      : extern.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include "add.hpp"

using namespace std;
int main(int argc, char **argv)
{
    std::cout << cnt << std::endl; 
    int c = add(1, 2);
    std::cout << c << std::endl;
    
    return 0;
}
