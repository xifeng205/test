/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-12 14:04
 * Last modified : 2020-05-12 14:04
 * Filename      : wchr_t.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char **argv)
{

    wchar_t a = 7;
    wchar_t b = '7';
    wchar_t c = L'7';
    cout << sizeof(a) << std::endl;
    cout << sizeof(b) << std::endl;
    cout << sizeof(c) << std::endl;

    cout << a << std::endl;
    cout << b << std::endl;
    cout << c << std::endl;
    return 0;
}
