/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-07-18 09:41
 * Last modified : 2020-07-18 09:41
 * Filename      : rvalue.cpp
 * Description   : 
*********************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    int  &&a = 10;
    cout << a << endl;
    return 0;
}
