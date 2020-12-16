/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-08-01 10:42
 * Last modified : 2020-08-01 10:42
 * Filename      : well_number.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

#define DOUBLE_WELL_NUMBLER
// #define WELL_NUMBER
#if defined WELL_NUMBER
int main(int argc, char **argv)
{
#define replace_name(name) #name
std::cout << replace_name(cuiyunpeng) << std::endl;

    return 0;
}
#elif defined DOUBLE_WELL_NUMBLER
int main(int argc, char **argv)
{
#define join(x, y) x##y
    int val = join(1, 2);
    cout << val << endl;
    
    return 0;
}
#endif
