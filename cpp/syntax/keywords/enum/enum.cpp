/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-12 14:49
 * Last modified : 2020-05-12 14:49
 * Filename      : enum.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    typedef enum {
        a,
        b,
        c,
        d
    } enum_t;

    enum_t f = d;
    cout << "The value of a is:" << f;
    return 0;
}
