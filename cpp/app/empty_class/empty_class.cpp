/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-28 13:03
 * Last modified : 2020-07-28 13:03
 * Filename      : empty_class.cpp
 * Description   : 
 *********************************************************************/

#include <cstddef>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    class empty {};
    size_t i = sizeof(empty);
    printf("%ld", i);
    empty empty__;
    i = sizeof(empty__);
    printf("%ld", i);
    return 0;
}
