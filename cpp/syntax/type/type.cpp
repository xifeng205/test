/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-05-12 14:11
 * Last modified : 2020-05-12 14:11
 * Filename      : type.cpp
 * Description   : 
*********************************************************************/

#include <iostream>
#include <limits>

using namespace std;

int main(int argc, char **argv)
{
    cout << "type \t\t" << "******size*******min********max****"<< endl;
    cout << "bool: \t\t" << "       " << sizeof(bool) << 
        "           " << (numeric_limits<bool>::min)()<<
        "           " << (numeric_limits<bool>::max)() << endl;
    cout << "char: \t\t" << "       " << sizeof(char) << 
        "           " << (numeric_limits<char>::min)()<<
        "           " << (numeric_limits<char>::max)() << endl;

    cout << "int: \t\t" << "       " << sizeof(int) << 
        "           " << (numeric_limits<int>::min)()<<
        "           " << (numeric_limits<int>::max)() << endl;

    cout << "long int: \t" << "       " << sizeof(long int) << 
        "           " << (numeric_limits<long int>::min)()<<
        "           " << (numeric_limits<long int>::max)() << endl;

    cout << "wchar_t: \t" << "       " << sizeof(wchar_t) << 
        "           " << (numeric_limits<wchar_t>::min)()<<
        "           " << (numeric_limits<wchar_t>::max)() << endl;
    cout << "type \t\t" << "*************emd*******************"<< endl;
    cout << "type \t\t" << "*************emd*******************"<< endl;

    return 0;
}
